/*
 * display.h
 *
 *  Created on: 2013年8月9日
 *      Author: umzhouc
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

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

#define MINPRESSURE 10
#define MAXPRESSURE 1000

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

unsigned long testText();

void initialDisplay();
void displayIdle();
void displayPayment();
void displayMenu(unsigned char pageNumber);
void displaySetting(unsigned char pageNumber);
void displayRefreshAmount();


void processTouch();




#endif /* DISPLAY_H_ */
