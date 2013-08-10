
#include "Arduino.h"


// IMPORTANT: Adafruit_TFTLCD LIBRARY MUST BE SPECIFICALLY
// CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Adafruit_TFTLCD.h FOR SETUP.

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// FOR TOUCH SCREEN ************************************************
// These are the pins for the shield!
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

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

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

unsigned long testText() {
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

void setup(void) {
  tft.reset();

  uint16_t identifier = tft.readID();

  tft.begin(identifier);

  tft.setRotation(1);
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000

void displayIdle()
{
	tft.fillScreen(BLACK);
	tft.drawLine(0, 30, 320, 30, RED);
	tft.drawLine(0, 60, 320, 60, RED);
	tft.drawLine(0, 120, 320, 120, RED);
	tft.drawLine(0, 180, 320, 180, RED);

	tft.setCursor(15, 7);
	tft.setTextColor(YELLOW);
	tft.setTextSize(2);
	tft.println("NFC Pay point v1.00.01");

	tft.setCursor(15, 37);
	tft.setTextSize(2);
	tft.println("Time: 00:00 2013-07-22");

	tft.setCursor(15, 75);
	tft.setTextSize(4);
	tft.println("Make payment");

	tft.setCursor(15, 135);
	tft.println("Menu");

	tft.setCursor(15, 195);
	tft.println("Setting");
}

void displayPayment()
{
	tft.fillScreen(BLACK);
	tft.drawLine(0, 60, 320, 60, RED);
	tft.drawLine(140, 120, 320, 120, RED);
	tft.drawLine(0, 180, 320, 180, RED);

	tft.drawLine(140, 0, 140, 240, RED);
	tft.drawLine(200, 0, 200, 240, RED);
	tft.drawLine(260, 0, 260, 240, RED);

	tft.setCursor(10, 15);
	tft.setTextColor(YELLOW);
	tft.setTextSize(4);
	tft.println("<exit");

	tft.setCursor(160, 15);
	tft.println("1");

	tft.setCursor(222, 15);
	tft.println("2");

	tft.setCursor(282, 15);
	tft.println("3");

	tft.setCursor(160, 75);
	tft.println("4");

	tft.setCursor(222, 75);
	tft.println("5");

	tft.setCursor(282, 75);
	tft.println("6");

	tft.setCursor(160, 135);
	tft.println("7");

	tft.setCursor(222, 135);
	tft.println("8");

	tft.setCursor(282, 135);
	tft.println("9");

	tft.setCursor(160, 195);
	tft.println(".");

	tft.setCursor(222, 195);
	tft.println("0");

	tft.setCursor(10, 195);
	tft.println(">OK");

	tft.setTextSize(3);
	tft.setCursor(266, 200);
	tft.println("Del");

	tft.setCursor(0, 0);
}

void displayMenu(unsigned char pageNumber)
{
	tft.fillScreen(BLACK);
	tft.drawLine(0, 60, 260, 60, RED);
	tft.drawLine(0, 120, 320, 120, RED);
	tft.drawLine(0, 180, 260, 180, RED);

	tft.drawLine(260, 0, 260, 240, RED);

	tft.setCursor(10, 15);
	tft.setTextColor(YELLOW);
	tft.setTextSize(4);
	tft.println("<exit");

	tft.setCursor(10, 75);
	tft.println("1. item 1");

	tft.setCursor(10, 135);
	tft.println("2. item 2");

	tft.setCursor(10, 195);
	tft.println("3. item 3");

	tft.drawLine(290, 25, 290, 95, RED);
	tft.drawLine(290, 25, 315, 50, RED);
	tft.drawLine(290, 25, 265, 50, RED);

	tft.drawLine(290, 145, 290, 215, RED);
	tft.drawLine(290, 215, 315, 190, RED);
	tft.drawLine(290, 215, 265, 190, RED);

	tft.setCursor(0, 0);
}

// 
void displaySetting(unsigned char pageNumber)
{
	tft.fillScreen(BLACK);
	tft.drawLine(0, 60, 260, 60, RED);
	tft.drawLine(0, 120, 320, 120, RED);
	tft.drawLine(0, 180, 260, 180, RED);

	tft.drawLine(260, 0, 260, 240, RED);

	tft.setCursor(10, 15);
	tft.setTextColor(YELLOW);
	tft.setTextSize(4);
	tft.println("<exit");

	tft.setCursor(10, 75);
	tft.println("1. item 1");

	tft.setCursor(10, 135);
	tft.println("2. item 2");

	tft.setCursor(10, 195);
	tft.println("3. item 3");

	tft.drawLine(290, 25, 290, 95, RED);
	tft.drawLine(290, 25, 315, 50, RED);
	tft.drawLine(290, 25, 265, 50, RED);

	tft.drawLine(290, 145, 290, 215, RED);
	tft.drawLine(290, 215, 315, 190, RED);
	tft.drawLine(290, 215, 265, 190, RED);

	tft.setCursor(0, 0);
}

// after user enter a price digit, display need to update the amount
void displayRefreshAmount()
{

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
			if(keyValue == 14 || keyValue == 4 || keyValue == 5 || keyValue == 6)
			{
				state = 2;
				moneyAmount = 0;
				displayPayment();
			}
			else if(keyValue == 15 || keyValue == 7 || keyValue == 8 || keyValue == 9)
			{
				state = 3;
				pageNumber = 0;
				displayMenu(0);
			}
			else if(keyValue == 16 || keyValue == 11 || keyValue == 10 || keyValue == 12)
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
			else if(keyValue == 14 || keyValue == 4 || keyValue == 5)
			{


			}


		}
		break;
	case 4: // Setting screen, waiting for user input
		if(keyPressed)
		{
			if(keyValue == 13)  // exit
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
			keyPressed = 0;
		}
		break;
	}
}

void processTouch()
{
	int x = 0;
	int y = 0;
	Point p = ts.getPoint();
	pinMode(XM, OUTPUT);
	pinMode(YP, OUTPUT);
	if (p.z > MINPRESSURE && p.z < MAXPRESSURE && keyPressed == 0)
	{
		keyPressed = 1;
		p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
		p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);

		x = p.y;
		y = 330 - p.x;

		if(y < 70)
		{
			if(x < 100) keyValue = 13;
			else if(x < 146) keyValue = 1;
			else if(x < 195) keyValue = 2;
			else keyValue = 3;
		}
		else if(y < 166)
		{
			if(x < 100) keyValue = 14;
			else if(x < 146) keyValue = 4;
			else if(x < 195) keyValue = 5;
			else keyValue = 6;
		}
		else if(y < 240)
		{
			if(x < 100) keyValue = 15;
			else if(x < 146) keyValue = 7;
			else if(x < 195) keyValue = 8;
			else keyValue = 9;
		}
		else
		{
			if(x < 100) keyValue = 16;
			else if(x < 146) keyValue = 11;
			else if(x < 195) keyValue = 10;
			else keyValue = 12;
		}

		tft.setTextColor(GREEN);
		tft.setTextSize(1);
		tft.print(keyValue);
		//tft.print(", ");
		//tft.print(y);
		tft.print(" ");
	}
}

void loop(void)
{
	processMain();
	processTouch();
}










