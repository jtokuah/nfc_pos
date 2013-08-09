
#include "Arduino.h"


// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#include "display.h"






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


void setup(void)
{
	initialDisplay();
}


int state = 0;

int keyPressed = 0; // 0: no key pressed, 1: key pressed
int keyValue = 0;

int moneyAmount = 0;

int pageNumber = 0;

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

void processMain()
{
	switch(state)
	{
	case 0: // display idle screen
		displayIdle();
		state = 1;
		state = 1; // ************************* for testing
		break;
	case 1: // Idle screen, waiting for user input
		if(keyPressed)
		{
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
			keyPressed = 0;
		}
		break;
	case 2: // Payment screen, waiting for user input
		if(keyPressed)
		{
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
			keyPressed = 0;
		}

		break;
	case 21: // The page after the merchant enter the price
		//
		state = 0;
		break;
	case 3: // Menu screen, waiting for user input
		if(keyPressed)
		{
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

			keyPressed = 0;
		}
		break;
	case 4: // Setting screen, waiting for user input
		if(keyPressed)
		{
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
			keyPressed = 0;
		}
		break;
	}
}



void loop(void)
{
	processMain();
	processTouch();
}










