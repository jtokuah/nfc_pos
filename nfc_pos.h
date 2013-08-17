/*
 * nfc_pos.h
 *
 *  Created on: 2013éªžï¿½é�ˆï¿½é�ƒï¿½
 *      Author: umzhouc
 */

#ifndef NFC_POS_H_
#define NFC_POS_H_

#define NFC //this should be defined by default.

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

#define MINPRESSURE 1
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

//
#define BACKGND1 0x33FFFF
#define TEXT1    0x0033
#define KEYS	 0x66B2FF

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define IRQ   (2)
#define RESET (3)

unsigned long testText();

void homeScreen_1();
void enterAmount_2(char * currentAmount);
void confirmSale_3(char * amount);
void mobileDetected_4(char * status);
void transactionResult_5(char * status, char * instruction);
void confirmation_6(char * receiptNum);
void cancelSale_7(char * currentAmount);

void progmemPrint(const char *str);
void progmemPrintln(const char *str);
void initialDisplay();
void displayIdle();
void displayPayment();
//void displayMenu(unsigned char pageNumber);
void displaySetting(unsigned char pageNumber);
void displayRefreshAmount();



void processTouch();

typedef struct cursorType {
	int hor;
	int ver;
}cursorType;

#ifdef NFC
void nfc_pos_configure_board(void);

/* Return type of the nfc_pos_transaction_handler() function */
typedef struct nfc_pos_transaction_result_type{
	int   status;
	int   transaction_ID;
	int   receipt_num;
	char  server_message[32];
}nfc_pos_transaction_result_type;

nfc_pos_transaction_result_type nfc_pos_transaction_handler(int moneyAmount, char* accountNum);

#endif


#endif /* NFC_POS_H_ */
