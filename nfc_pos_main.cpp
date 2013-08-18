#include "Arduino.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <stdarg.h>
#include <stdio.h>
#include "nfc_pos.h"

int state = 0;
int keyValue = 0;
int screenPressed = 0;

int authCode = -1;
int pageNumber = 0;
int pageDelay = 1000;
char* accountNum = "AC123456";
char saleAmount [MAX_NUM_DIGITS+1];
bool pointEntered = false;
nfc_pos_touch_region_type  selected;

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

//This is the main function of the program
void processMain()
{
#ifdef NFC
	nfc_pos_transaction_result_type transactionResult;
#endif
	switch(state)
	{
		case 0: // display idle screen
			homeScreen();
			state = 1;
			state = 1; // ************************* HACK point
			break;
		case 1: // Idle screen, waiting for user input
			progmemPrintln(PSTR("processMain: state 1"));
			while (state == 1)
			{
				selected = touchedRegion(TOUCH_SCREEN_HOME_SCREEN);
				if(selected == TOUCH_REGION_HOME_SALE) // select make payment
				{
					state = 2;
					saleAmount [0]= '\0';
					getSaleAmount(saleAmount);
				}
			}
			break;
		case 2: // Payment screen, waiting for user input
			progmemPrintln(PSTR("processMain: state 2"));
			while(state == 2)
			{
				selected = touchedRegion(TOUCH_SCREEN_GET_SALE_AMOUNT);
				if ((selected == TOUCH_REGION_KEYBOARD_1) && (strlen(saleAmount)<MAX_NUM_DIGITS))
				{
					strlcat(saleAmount, "1", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_2) && (strlen(saleAmount)<MAX_NUM_DIGITS))
				{
					strlcat(saleAmount, "2", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_3) && (strlen(saleAmount)<MAX_NUM_DIGITS))
				{
					strlcat(saleAmount, "3", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_4) && (strlen(saleAmount)<MAX_NUM_DIGITS))
				{
					strlcat(saleAmount, "4", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_5) && (strlen(saleAmount)<MAX_NUM_DIGITS))
				{
					strlcat(saleAmount, "5", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_6) && (strlen(saleAmount)<MAX_NUM_DIGITS))
				{
					strlcat(saleAmount, "6", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_7) && (strlen(saleAmount)<MAX_NUM_DIGITS))
				{
					strlcat(saleAmount, "7", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_8) && (strlen(saleAmount)<MAX_NUM_DIGITS))
				{
					strlcat(saleAmount, "8", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_9) && (strlen(saleAmount)<MAX_NUM_DIGITS))
				{
					strlcat(saleAmount, "9", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_DOT) && (strlen(saleAmount)<MAX_NUM_DIGITS-1) && (!pointEntered))
				{
					strlcat(saleAmount, ".", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
					pointEntered = true;
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_0) && (strlen(saleAmount)<MAX_NUM_DIGITS))
				{
					strlcat(saleAmount, "0", MAX_NUM_DIGITS-1);
					getSaleAmount(saleAmount);
				}
				else if (selected == TOUCH_REGION_KEYBOARD_CAN)
				{
					state = 6;
					cancelSale(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_COR))
				{
					saleAmount[strlen(saleAmount)-1] = '\0';
					getSaleAmount(saleAmount);
				}
				else if ((selected == TOUCH_REGION_KEYBOARD_OK))
				{
					state = 3;
					confirmSale(saleAmount);
				}
			}
			break;
		case 3:
			while (state == 3)
			{
#ifdef NFC
				progmemPrintln(PSTR("processMain:: state 3"));
				progmemPrintln(PSTR("processmain:: Detecting mobile phone"));
				transactionResult = nfc_pos_transaction_handler(saleAmount, accountNum);
				if (transactionResult.status != -1)
				{
					confirmation(transactionResult.receipt_num);
					progmemPrintln(PSTR("processmain:: payment successful!"));
					pageDelay = 1000;
					while (pageDelay > 0)
					{
						pageDelay --;
					}
				}
				else
				{
					progmemPrintln(PSTR("processmain:: Unexpected error."));
				}
#endif
			state = 0;
			}
			break;
		case 6:
			progmemPrintln(PSTR("processMain: state 6"));
			while(state == 6)
			{
				selected = touchedRegion(TOUCH_SCREEN_CANCEL_SALE);
				if (selected == TOUCH_REGION_CAN_CANCEL)
				{
					state = 0;
				}
				else if (selected == TOUCH_REGION_CAN_CONTINUE)
				{
					state = 2;
					getSaleAmount(saleAmount);
				}
			}
			break;
		default:
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










