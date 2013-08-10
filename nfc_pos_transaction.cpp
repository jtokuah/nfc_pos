#include <nfc_pos.h>
#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define IRQ   (2)
#define RESET (3)

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

char DataOut[]="HELLO BLCAKBERRY!"; //HACK 16bytes
char DataIn[16];//HACK Should be 16bytes


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
	 // Configure PN532 as Peer to Peer Target
 if(nfc.inListPassiveTarget()) //if connection is error-free
 {
	//trans-receive data
	if(nfc.inDataExchange(DataOut, (uint8_t)sizeof(DataOut), DataIn, (uint8_t*)sizeof(DataIn)))
	{
	  Serial.print("Data Received1: ");
	  Serial.println(DataIn);
	  tft.print("Data Received1: ");
	  tft.println(DataIn);
	}
	//trans-receive data
	if(nfc.inDataExchange(DataOut, (uint8_t)sizeof(DataOut), DataIn, (uint8_t*)sizeof(DataIn)))
	{
	  Serial.print("Data Received2: ");
	  Serial.println(DataIn);
	  tft.print("Data Received2: ");
	  tft.println(DataIn);
	}
	//trans-receive data
	if(nfc.inDataExchange(DataOut, (uint8_t)sizeof(DataOut), DataIn, (uint8_t*)sizeof(DataIn)))
	{
	  Serial.print("Data Received3: ");
	  Serial.println(DataIn);
	  tft.print("Data Received3: ");
	  tft.println(DataIn);
	}
 }
}
