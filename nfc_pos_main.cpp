#include "Arduino.h"


// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <stdarg.h>
#include <stdio.h>
#include "nfc_pos.h"


// FOR TOUCH SCREEN END *********************************************

// When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
// For the Arduino Uno, Duemilanove, Diecimila, etc.:
//   D0 connects to digital pin 8  (Notice these are
//   D1 connects to digital pin 9   NOT in order!)
//   D2 connects to digital pin 2
//   D3 connects to digital pin 3
//   D4 connects to digital pin 4
//   D5 connects to digital pin 5
//   D6 connects to digital pin 6
//   D7 connects to digital pin 7
// For the Arduino Mega, use digital pins 22 through 29
// (on the 2-row header at the end of the board).


int state = 0;
int keyValue = 0;
int keyPressed = 0;
int moneyAmount = -1;
int authCode = -1;
int pageNumber = 0;
char* accountNum = "";

/*char * menuStr [10];
menuStr[0] = "item 01";
menuStr[1] = "item 02";
menuStr[2] = "item 03";
menuStr[3] = "item 04";
menuStr[4] = "item 05";
menuStr[5] = "item 06";
menuStr[6] = "item 07";
menuStr[7] = "item 08";
menuStr[8] = "item 09";
menuStr[9] = "item 10";*/

/* ***************Please read the following*********************
	1. number are represented in int. "123.45" in variable is 12345
	2. 

*/

// Copy string from flash to serial port
// Source string MUST be inside a PSTR() declaration!
void progmemPrint(const char *str) {
  char c;
  while(c = pgm_read_byte(str++)) Serial.print(c);
}

// Same as above, with trailing newline
void progmemPrintln(const char *str) {
  progmemPrint(str);
  Serial.println();
}

boolean nfc_pos_verify_transaction(int code)
{
	return true;
}


void processMain()
{
#ifdef NFC
	nfc_pos_transaction_result_type transactionResult;
#endif

	processTouch();

	switch(state)
	{
	case 0: // display idle screen
		displayIdle();
		state = 1;
		state = 1; // ************************* for testing
		break;
	case 1: // Idle screen, waiting for user input
		if(processTouch())
		{
			progmemPrintln(PSTR("processMain: case 1"));
			if(keyValue == 14 || keyValue == 4 || keyValue == 5 || keyValue == 6) // select make payment
			{
				state = 2;
				moneyAmount = 0;
				displayPayment();
			}
			else if(keyValue == 15 || keyValue == 7 || keyValue == 8 || keyValue == 9) // select menu
			{
				state = 3;
				pageNumber = 0;
				displayMenu(0);
			}
			else if(keyValue == 16 || keyValue == 11 || keyValue == 10 || keyValue == 12) // setting
			{
				state = 4;
				pageNumber = 0;
				displaySetting(0);
			}
			state = 21; //JT: HACK
		}
		break;
	case 2: // Payment screen, waiting for user input
		if(processTouch())
		{
			progmemPrintln(PSTR("processMain: case 2"));
			if(keyValue == 13) // exit
				state = 0;
			else if(keyValue == 1) // input = number
			{
				moneyAmount = moneyAmount * 10 + keyValue;
				displayRefreshAmount();
			}
			else if(keyValue == 16) // confirm
			{
				state = 21;

			}
			else if(keyValue == 11) // . current not used
			{

			}
			else if(keyValue == 12) // backspace
			{
				moneyAmount = moneyAmount / 10;
				displayRefreshAmount();
			}
		}
		break;
	case 21: // Payment transaction
		progmemPrintln(PSTR("processMain:: case 21"));
		moneyAmount = 50; //JT:HACK
		accountNum = "AC123456"; //JT:HACK -
		displayTransaction();
		displayLine("Detecting mobile phone...");
		progmemPrintln(PSTR("processmain:: Detecting mobile phone"));
#ifdef NFC
		transactionResult = nfc_pos_transaction_handler(moneyAmount, accountNum);
		if (transactionResult.status != -1){
			//verify authentication code
			if (nfc_pos_verify_transaction(transactionResult.receipt_num))
			{
				displayLine("Approved!");
				progmemPrintln(PSTR("processmain:: payment successful!"));
			}
			else
			{
				displayLine("Not Approved!.");
				progmemPrintln(PSTR("processmain:: invalid receipt" ));
			}
		}
		else
		{
			progmemPrintln(PSTR("processmain:: Unexpected error."));
			displayLine("Unexpected error!");
		}
#endif
		processTouch();
		state = 0; // JT:HACK
		break;
	case 3: // Menu screen, waiting for user input
		if(processTouch())
		{
			progmemPrintln(PSTR("processMain:: case 3"));
			if(keyValue == 13 || keyValue == 1 || keyValue == 2)  // exit
			{
				state = 0;
			}
			else if(keyValue == 3 || keyValue == 6) // page up
			{
				pageNumber ++;
				displayMenu(pageNumber);
			}
			else if(keyValue == 9 || keyValue == 12) // page down
			{
				pageNumber --;
				displayMenu(pageNumber);
			}
			else if(keyValue == 14 || keyValue == 4 || keyValue == 5) // select item 1
			{
				state = 30 + pageNumber * 3;
				state = 0;
			}
			else if(keyValue == 15 || keyValue == 7 || keyValue == 8) // select item 2
			{
				state = 31 + pageNumber * 3;
				state = 0;
			}
			else if(keyValue == 15 || keyValue == 7 || keyValue == 8) // select item 3
			{
				state = 32 + pageNumber * 3;
				state = 0;
			}
		}
		break;
	case 4: // Setting screen, waiting for user input
		if(processTouch())
		{
			progmemPrintln(PSTR("processMain:: case 4"));
			if(keyValue == 13 || keyValue == 1 || keyValue == 2)  // exit
			{
				state = 0;
			}
			else if(keyValue == 3 || keyValue == 6) // page up
			{
				displayMenu(0);
			}
			else if(keyValue == 9 || keyValue == 12) // page down
			{
				displayMenu(0);
			}
			else if(keyValue == 14 || keyValue == 4 || keyValue == 5) // select item 1
			{
				state = 40 + pageNumber * 3;
				state = 0;
			}
			else if(keyValue == 15 || keyValue == 7 || keyValue == 8) // select item 2
			{
				state = 41 + pageNumber * 3;
				state = 0;
			}
			else if(keyValue == 15 || keyValue == 7 || keyValue == 8) // select item 3
			{
				state = 42 + pageNumber * 3;
				state = 0;
			}
		}
		break;
	}
}

void setup(void)
{
	Serial.begin(115200);
	initialDisplay();
#ifdef NFC
	progmemPrintln(PSTR("NFC Point of Sale Payment Solution\n"));
	nfc_pos_configure_board();
#endif
}

void loop(void)
{
	processMain();
}










