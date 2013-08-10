#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#include "nfc_pos.h"

#define IRQ   (2)
#define RESET (3)

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

char DataOut1[]="Connecting..."; //HACK 16bytes
char DataOut2[]="Authenticating..."; //HACK 16bytes
char DataOut3[]="Approved"; //HACK 16bytes
char DataIn1[sizeof(DataOut1)];//HACK Should be 16bytes
char DataIn2[sizeof(DataOut2)];//HACK Should be 16bytes
char DataIn3[sizeof(DataOut3)];//HACK Should be 16bytes


void nfc_pos_chip_config(void){
	Serial.begin(115200);
	nfc.begin();

	uint32_t versiondata = nfc.getFirmwareVersion();
	if (! versiondata) {
	Serial.print("Didn't find PN53x board");
	while (1); // halt
	}
	// Got ok data, print it out!
	Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
	Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
	Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

	// configure board to read RFID tags and cards
	nfc.SAMConfig();
}

void nfc_pos_transact(void) {
	 nfc_pos_chip_config();

	 // Configure PN532 as Peer to Peer Target
 if(nfc.inListPassiveTarget()) //if connection is error-free
 {
	//trans-receive data
	if(nfc.inDataExchange(DataOut1, (uint8_t)sizeof(DataOut1), DataIn1, (uint8_t*)sizeof(DataIn1)))
	{
	  printLine(DataIn1);
	  Serial.println(DataIn1);
	}
	//trans-receive data
	if(nfc.inDataExchange(DataOut2, (uint8_t)sizeof(DataOut2), DataIn2, (uint8_t*)sizeof(DataIn2)))
	{
	  printLine(DataIn2);
	  Serial.println(DataIn2);
	}
	//trans-receive data
	if(nfc.inDataExchange(DataOut3, (uint8_t)sizeof(DataOut3), DataIn3, (uint8_t*)sizeof(DataIn3)))
	{
	  printLine(DataIn3);
	  Serial.println(DataIn3);
	}
 }
}
