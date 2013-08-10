#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>
#include <errno.h>

#include "nfc_pos.h"

#define IRQ   (2)
#define RESET (3)

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

static int transaction_ID = -1;

/*
 * Configure NFC board
 */
void nfc_pos_configure_board(void){
	Serial.begin(115200);
	nfc.begin();

	uint32_t versiondata = nfc.getFirmwareVersion();
	if (! versiondata) {
	ERRORF("Didn't find PN53x board");
	while (1); // halt
	}
	// Got ok data, print it out!
  	Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
  	Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
  	Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

	// configure board to read RFID tags and cards
	nfc.SAMConfig();
}

/*
 * Create unique transaction ID
 */
int nfc_pos_generate_transaction_ID(){

}

int nfc_pos_transact(int paymentAmount) {
	int status = 0;


	nfc_pos_configure_board();

	char DataOut1[]="Connecting to server...";
	char DataOut2[] = "";
	sprintf(DataOut2, "Authenticating $ %d", paymentAmount);
	char DataOut3[]="Payment completed";
	char DataIn1[sizeof(DataOut1)];
	char DataIn2[sizeof(DataOut2)];
	char DataIn3[sizeof(DataOut3)];

	 // Configure PN532 as Peer to Peer Target
	if(nfc.inListPassiveTarget()) //if connection is error-free
	{
		//trans-receive data
		if(nfc.inDataExchange(DataOut1, (uint8_t)sizeof(DataOut1), DataIn1, (uint8_t*)sizeof(DataIn1)))
		{
		  displayLine(DataIn1);
		  Serial.println(DataIn1);
		}
		//trans-receive data
		if(nfc.inDataExchange(DataOut2, (uint8_t)sizeof(DataOut2), DataIn2, (uint8_t*)sizeof(DataIn2)))
		{
		  displayLine(DataIn2);
		  Serial.println(DataIn2);
		}
		//trans-receive data
		if(nfc.inDataExchange(DataOut3, (uint8_t)sizeof(DataOut3), DataIn3, (uint8_t*)sizeof(DataIn3)))
		{
		  displayLine(DataIn3);
		  Serial.println(DataIn3);
		}
	 }
	 return status;
}
