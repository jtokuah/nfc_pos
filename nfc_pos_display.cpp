#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#include "nfc_pos.h"

#include "Arduino.h"

//Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
Adafruit_TFTLCD tft;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen touchScreen = TouchScreen(XP, YP, XM, YM, 300);

extern long moneyAmount; // the transaction amount
int keyDelay = 0; // the time between any 2 key is pressed

static cursorType cursor;

nfc_pos_touch_input_table_entry touch_table[TOUCH_REGION_MAX] PROGMEM = {
	//Home screen menu
	{TOUCH_REGION_HOME_SALE, 140, 240, 100, 175},
	{TOUCH_REGION_HOME_ACCOUNT, 100, 240, 176, 245},
	{TOUCH_REGION_HOME_ADMIN, 120, 240, 246, 300},

	//keypad
	{TOUCH_REGION_KEYBOARD_1, 10, 84, 80, 126},
	{TOUCH_REGION_KEYBOARD_2, 85, 158, 80, 126},
	{TOUCH_REGION_KEYBOARD_3, 159, 232, 80, 126},
	{TOUCH_REGION_KEYBOARD_4, 10, 84, 127, 172},
	{TOUCH_REGION_KEYBOARD_5, 85, 158, 127, 172},
	{TOUCH_REGION_KEYBOARD_6, 159, 232, 127, 172},
	{TOUCH_REGION_KEYBOARD_7, 10, 84, 173, 218},
	{TOUCH_REGION_KEYBOARD_8, 85, 158, 173, 218},
	{TOUCH_REGION_KEYBOARD_9, 159, 232, 173, 218},
	{TOUCH_REGION_KEYBOARD_DOT, 10, 84, 219, 263},
	{TOUCH_REGION_KEYBOARD_0, 85, 158, 219, 263},
	{TOUCH_REGION_KEYBOARD_HASH, 159, 232, 219, 263},
	{TOUCH_REGION_KEYBOARD_CAN, 10, 84, 264, 310},
	{TOUCH_REGION_KEYBOARD_COR, 85, 158, 264, 310},
	{TOUCH_REGION_KEYBOARD_OK, 159, 232, 263, 310},

	//Cancel sale
	{TOUCH_REGION_CAN_CANCEL, 20, 220, 173, 217},
	{TOUCH_REGION_CAN_CONTINUE, 20, 220, 229, 273}
};

unsigned long testText(){
	tft.fillScreen(BLACK);
	unsigned long start = micros();
	tft.setCursor(0, 0);
	tft.setTextColor(WHITE);  tft.setTextSize(1);
	tft.println("Hello World!");
	tft.setTextColor(YELLOW); tft.setTextSize(2);
	tft.println(1234.56);
	tft.setTextColor(RED);    tft.setTextSize(3);
	tft.println(0xDEADBEEF, HEX);
	tft.println();
	tft.setTextColor(GREEN);
	tft.setTextSize(5);
	tft.println("Groop");
	tft.setTextSize(2);
	tft.println("I implore thee,");
	tft.setTextSize(1);
	tft.println("my foonting turlingdromes.");
	tft.println("And hooptiously drangle me");
	tft.println("with crinkly bindlewurdles,");
	tft.println("Or I will rend thee");
	tft.println("in the gobberwarts");
	tft.println("with my blurglecruncheon,");
	tft.println("see if I don't!");
	return micros() - start;
}

void initialDisplay()
{
	tft.reset();

	uint16_t identifier = tft.readID();

	tft.begin(identifier);

	tft.setRotation(0);
}

void homeScreen()
{
    tft.fillScreen(BACKGND1);

	tft.setCursor(15, 10);
	tft.setTextColor(TEXT1);
	tft.setTextSize(2);
	tft.println(" NFC POS Solution");

	tft.setCursor(180, 140);
	tft.println("Sale");

	tft.setCursor(150, 210);
	tft.println("Account");

	tft.setCursor(170, 	280);
	tft.println("Admin");
}

//This replaces the displayPayment() function
void getSaleAmount(const char currentAmount[])
{
	progmemPrintln(PSTR("getSaleAMount:: pushing Screen"));
	//set background colour
	tft.fillScreen(BACKGND1);

	tft.setCursor(10, 10);
	tft.setTextColor(TEXT1);
	tft.setTextSize(2);
	tft.println("Enter sale amount:");

	//ensure the '$' symbol is placed correctly
	tft.setCursor(219-(13*strlen(currentAmount)), 50);
	tft.println("$");

	tft.setCursor(232-(13*strlen(currentAmount)), 50);
	tft.println(currentAmount);

	tft.setTextSize(3);

	//line 1
	tft.fillRoundRect(10, 80, 73, 45, 10, KEYS);
	tft.drawRoundRect(85, 80, 72, 45, 10, TEXT1);
	tft.fillRoundRect(159, 80, 73, 45, 10, KEYS);
	tft.setCursor(4, 93);
	tft.println("  1   2   3  "); //do not edit this line

	//line 2
	tft.fillRoundRect(10, 127, 73, 44, 10, KEYS);
	tft.drawRoundRect(85, 127, 72, 44, 10, TEXT1);
	tft.fillRoundRect(159, 127, 73, 44, 10, KEYS);
	tft.setCursor(4, 138);
	tft.println("  4   5   6  ");//do not edit this line

	//line 3
	tft.fillRoundRect(10, 173, 73, 44, 10, KEYS);
	tft.drawRoundRect(85, 173, 72, 44, 10, TEXT1);
	tft.fillRoundRect(159, 173, 73, 44, 10, KEYS);
	tft.setCursor(4, 183);
	tft.println("  7   8   9  ");//do not edit this line

	//line 4
	tft.fillRoundRect(10, 219, 73, 44, 10, KEYS);
	tft.drawRoundRect(85, 219, 72, 44, 10, TEXT1);
	tft.fillRoundRect(159, 219, 73, 44, 10, KEYS);
	tft.setCursor(4, 227);
	tft.println("  .   0   #  ");//do not edit this line

	//line 5
	tft.fillRoundRect(10, 264, 73, 46, 10, RED);
	tft.fillRoundRect(85, 264, 72, 46, 10, YELLOW);
	tft.fillRoundRect(159,264, 73, 46, 10, GREEN);
	tft.setCursor(2, 275);
	tft.println(" CAN COR  OK ");//do not edit this line
}


void confirmSale(const char amount[])
{
	tft.fillScreen(BACKGND1);

	tft.setCursor(10, 10);
	tft.setTextColor(TEXT1);
	tft.setTextSize(2);
	tft.println("Sale");

	tft.setCursor(10, 50);
	tft.println("Total:$");

	tft.setCursor(170, 50);
	tft.println(amount);

	tft.setCursor(30, 220);
	tft.println("Place Mobile on");
	tft.setCursor(50, 250);
	tft.println("the NFC Area");
}

void mobileDetected(char * status)
{
    tft.fillScreen(BACKGND1);

	tft.setCursor(10, 10);
	tft.setTextColor(TEXT1);
	tft.setTextSize(2);
	tft.println("Sale");

	tft.setCursor(40, 110);
	tft.setTextColor(RED);
	tft.println("DO NOT REMOVE");
	tft.setCursor(80,130);
	tft.println("MOBILE!");
	tft.setTextColor(TEXT1);

	tft.setCursor(10, 290);
	tft.println(status);  //JT:HACK
}

void transactionResult(char * status, char * instruction)
{
    tft.fillScreen(BACKGND1);

	tft.setCursor(10, 10);
	tft.setTextColor(TEXT1);
	tft.setTextSize(2);
	tft.println("Sale");

	tft.setCursor(10, 260);
	tft.println(status);  //JT:HACK

	tft.setCursor(10, 290);
	tft.println(instruction);  //JT:HACK
}

void confirmation(char * receiptNum)
{
    tft.fillScreen(BACKGND1);

	tft.setCursor(10, 10);
	tft.setTextColor(TEXT1);
	tft.setTextSize(2);
	tft.println("Sale");


	tft.setCursor(60, 130);
	tft.setTextColor(GREEN);
	tft.println("APPROVED");
	tft.setTextColor(TEXT1);

	tft.setCursor(10, 260);
	tft.println("Receipt #: ");

	tft.setCursor(10, 290);
	tft.println(receiptNum);
}

void cancelSale(const char currentAmount[])
{
	//set background colour
	tft.fillScreen(BACKGND1);

	tft.setCursor(10, 10);
	tft.setTextColor(TEXT1);
	tft.setTextSize(2);
	tft.println("Sale");

	//ensure the '$' symbol is placed correctly
	tft.setCursor((157+(13*(5-strlen(currentAmount)))), 50);
	tft.println("$");

	tft.setCursor((170+(13*(5-strlen(currentAmount)))), 50);
	tft.println(currentAmount);

	tft.setCursor(50, 130);
	tft.println("Cancel Sale?");

	tft.setTextSize(3);

	tft.fillRoundRect(20, 173, 200, 44, 10, RED);
	tft.setCursor(65, 182);
	tft.println("CANCEL");

	tft.fillRoundRect(20, 229, 200, 44, 10, GREEN);
	tft.setCursor(50, 238);
	tft.println("CONTINUE");
}


/*
 * This function handles touch events
 */
nfc_pos_touch_region_type  touchedRegion(nfc_pos_touch_screen_type screen)
{
	int x = 0;
	int y = 0;
	bool keyPressed = false;
	Point point;

	while (true)
	{
		    point = touchScreen.getPoint();
			pinMode(XM, OUTPUT);
			pinMode(YP, OUTPUT);

			int debounce = 200;
			while ((point.z > MINPRESSURE) && (point.z < MAXPRESSURE) && debounce>0)
			{
				debounce --;
			}

			if (debounce == 0){
				keyPressed = true;
			}

			if (keyPressed){
				point.x = map(point.x, TS_MINX, TS_MAXX, tft.width(), 0 );
				point.y = map(point.y, TS_MINY, TS_MAXY, tft.height(), 0 );
				progmemPrint(PSTR("touchedRegion():: x = "));Serial.print(point.x);
				progmemPrint(PSTR(", y = "));Serial.println(point.y);

				switch(screen)
				{
					case TOUCH_SCREEN_HOME_SCREEN:
						if((touch_table[TOUCH_REGION_HOME_SALE].left<=point.x) && (point.x<touch_table[TOUCH_REGION_HOME_SALE].right) &&
								(touch_table[TOUCH_REGION_HOME_SALE].top<=point.y) && (point.y<touch_table[TOUCH_REGION_HOME_SALE].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():'Sale' Selected"));
							return TOUCH_REGION_HOME_SALE;
						}
						break;
					case TOUCH_SCREEN_GET_SALE_AMOUNT:
						if((touch_table[TOUCH_REGION_KEYBOARD_1].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_1].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_1].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_1].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '1' Pressed"));
							return TOUCH_REGION_KEYBOARD_1;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_2].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_2].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_2].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_2].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '2' Pressed"));
							return TOUCH_REGION_KEYBOARD_2;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_3].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_3].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_3].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_3].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '3' Pressed"));
							return TOUCH_REGION_KEYBOARD_3;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_4].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_4].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_4].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_4].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '4' Pressed"));
							return TOUCH_REGION_KEYBOARD_4;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_5].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_5].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_5].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_5].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '5' Pressed"));
							return TOUCH_REGION_KEYBOARD_5;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_6].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_6].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_6].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_6].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '6' Pressed"));
							return TOUCH_REGION_KEYBOARD_6;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_7].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_7].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_7].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_7].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '7' Pressed"));
							return TOUCH_REGION_KEYBOARD_7;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_8].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_8].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_8].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_8].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '8' Pressed"));
							return TOUCH_REGION_KEYBOARD_8;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_9].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_9].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_9].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_9].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '9' Pressed"));
							return TOUCH_REGION_KEYBOARD_9;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_DOT].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_DOT].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_DOT].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_DOT].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '.' Pressed"));
							return TOUCH_REGION_KEYBOARD_DOT;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_0].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_0].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_0].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_0].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '0' Pressed"));
							return TOUCH_REGION_KEYBOARD_0;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_HASH].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_HASH].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_HASH].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_HASH].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key '#' Pressed"));
							return TOUCH_REGION_KEYBOARD_HASH;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_CAN].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_CAN].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_CAN].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_CAN].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key 'CAN' Pressed"));
							return TOUCH_REGION_KEYBOARD_CAN;
						}
						else if((touch_table[TOUCH_REGION_KEYBOARD_OK].left<=point.x) && (point.x<touch_table[TOUCH_REGION_KEYBOARD_OK].right) &&
								(touch_table[TOUCH_REGION_KEYBOARD_OK].top<=point.y) && (point.y<touch_table[TOUCH_REGION_KEYBOARD_OK].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key 'OK' Pressed"));
							return TOUCH_REGION_KEYBOARD_OK;
						}
						break;
					case TOUCH_SCREEN_CANCEL_SALE:
						if((touch_table[TOUCH_REGION_CAN_CANCEL].left<=point.x) && (point.x<touch_table[TOUCH_REGION_CAN_CANCEL].right) &&
								(touch_table[TOUCH_REGION_CAN_CANCEL].top<=point.y) && (point.y<touch_table[TOUCH_REGION_CAN_CANCEL].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key 'CANCEL' Pressed"));
							return TOUCH_REGION_CAN_CANCEL;
						}
						else if((touch_table[TOUCH_REGION_CAN_CONTINUE].left<=point.x) && (point.x<touch_table[TOUCH_REGION_CAN_CONTINUE].right) &&
								(touch_table[TOUCH_REGION_CAN_CONTINUE].top<=point.y) && (point.y<touch_table[TOUCH_REGION_CAN_CONTINUE].bottom))
						{
							progmemPrintln(PSTR("touchedRegion():Key 'CONTINUE' Pressed"));
							return TOUCH_REGION_CAN_CONTINUE;
						}
					break;
					default:
						break;
				}
				keyPressed = false;
			}
	}
	return TOUCH_REGION_NONE;

}

