#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>

#include "nfc_pos.h"

#include "Arduino.h"



Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
// If using the shield, all control and data lines are fixed, and
// a simpler declaration can optionally be used:
// Adafruit_TFTLCD tft;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

extern int keyPressed ; // 0: no key pressed, 1: key pressed
extern int keyValue;
static cursorType cursor;

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

void initialDisplay()
{
  tft.reset();

  uint16_t identifier = tft.readID();

  tft.begin(identifier);

  tft.setRotation(1);
}

void displayUpdates()
{
	cursor.hor = 15;
	cursor.ver = 37;
    tft.fillScreen(BLACK);
	tft.drawLine(0, 30, 320, 30, RED);
	tft.setCursor(cursor.hor, cursor.ver);
	tft.setTextColor(YELLOW);
	tft.setTextSize(2);
}

void printLine(char *line)
{
	tft.println(line);
	cursor.ver += 15;
	tft.setCursor(cursor.hor, cursor.ver);
}

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
