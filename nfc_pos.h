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
#define MAXPRESSURE 10000

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

//#define TS_MINX 0
//#define TS_MINY 0
//#define TS_MAXX 240
//#define TS_MAXY 320


#define IRQ   (2)
#define RESET (3)

#define MAX_NUM_DIGITS 12

unsigned long testText();

void homeScreen();
void getSaleAmount(const char currentAmount[]);
void confirmSale(const char amount[]);
void mobileDetected(char * status);
void transactionResult(char * status, char * instruction);
void confirmation(char * receiptNum);
void cancelSale(const char currentAmount[]);

void progmemPrint(const char *str);
void progmemPrintln(const char *str);
void initialDisplay();
void displayIdle();
void displayPayment();
//void displayMenu(unsigned char pageNumber);
void displaySetting(unsigned char pageNumber);
void displayRefreshAmount();


typedef struct cursorType {
	uint16_t hor;
	uint16_t ver;
}cursorType;

#ifdef NFC
void nfc_pos_configure_board(void);

/* Return type of the nfc_pos_transaction_handler() function */
typedef struct nfc_pos_transaction_result_type{
	int   status;
	int   transaction_ID;
	char*   receipt_num;
	char  server_message[32];
}nfc_pos_transaction_result_type;

nfc_pos_transaction_result_type nfc_pos_transaction_handler(char* moneyAmount, char* accountNum);

#endif

typedef enum {
	TOUCH_REGION_NONE = -1,
	TOUCH_REGION_HOME_SALE = 0,
	TOUCH_REGION_HOME_ACCOUNT,
	TOUCH_REGION_HOME_ADMIN,
	TOUCH_REGION_KEYBOARD_1,
	TOUCH_REGION_KEYBOARD_2,
	TOUCH_REGION_KEYBOARD_3,
	TOUCH_REGION_KEYBOARD_4,
	TOUCH_REGION_KEYBOARD_5,
	TOUCH_REGION_KEYBOARD_6,
	TOUCH_REGION_KEYBOARD_7,
	TOUCH_REGION_KEYBOARD_8,
	TOUCH_REGION_KEYBOARD_9,
	TOUCH_REGION_KEYBOARD_DOT,
	TOUCH_REGION_KEYBOARD_0,
	TOUCH_REGION_KEYBOARD_HASH,
	TOUCH_REGION_KEYBOARD_CAN,
	TOUCH_REGION_KEYBOARD_COR,
	TOUCH_REGION_KEYBOARD_OK,
	TOUCH_REGION_CAN_CANCEL,
	TOUCH_REGION_CAN_CONTINUE,
	//all new regions should be added above this line
	TOUCH_REGION_MAX,
}nfc_pos_touch_region_type;

typedef enum{
	TOUCH_SCREEN_INVALID_SCREEN = -1,
	TOUCH_SCREEN_HOME_SCREEN = 0,
	TOUCH_SCREEN_GET_SALE_AMOUNT,
	TOUCH_SCREEN_CANCEL_SALE
}nfc_pos_touch_screen_type;

typedef struct {
	nfc_pos_touch_region_type region_name;
	uint16_t left;
	uint16_t right;
	uint16_t top;
	uint16_t bottom;
}nfc_pos_touch_input_table_entry;

nfc_pos_touch_region_type  touchedRegion(nfc_pos_touch_screen_type screen);


#endif /* NFC_POS_H_ */
