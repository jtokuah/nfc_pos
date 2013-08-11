#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>
#include <errno.h>

#include "nfc_pos.h"
#include "nfc_pos_transaction.h"

#define IRQ   (2)
#define RESET (3)

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

nfc_pos_incoming_transaction_table_entry incoming_table [INCOMING_CODE_MAX] =
{
	{INCOMING_CODE_MESSAGE_ACK, (char*)"00"},
	{INCOMING_CODE_PEER_DEVICE_READY_RESPONSE, (char*)"01"},
	{INCOMING_CODE_PAYMENT_AMOUNT_RECEIVED_CONFIRMATION, (char*)"02"},
	{INCOMING_CODE_MERCHANT_ACCT_NUM_RECEIVED_CONFIRMATION, (char*)"03"},
	{INCOMING_CODE_SERVER_CONNECTION_SUCCESSFUL, (char*)"04"},
	{INCOMING_CODE_SERVER_CONNECTION_FAILED, (char*)"05"},
	{INCOMING_CODE_MERCHANT_AUTHENTICATION_SUCCESSFUL, (char*)"06"},
	{INCOMING_CODE_MERCHANT_AUTHENTICATION_FAILED, (char*)"07"},
	{INCOMING_CODE_CUSTOMER_AUTHENTICATION_SUCCESSFUL, (char*)"08"},
	{INCOMING_CODE_CUSTOMER_AUTHENTICATION_FAILED, (char*)"09"},
	{INCOMING_CODE_INSUFFICIENT_FUNDS_RESULT, (char*)"10"},
	{INCOMING_CODE_TRANSACTION_SUCCESSFUL, (char*)"11"},
	{INCOMING_CODE_TRANSACTION_FAILED, (char*)"12"},
	{INCOMING_CODE_READY_FOR_RECEPT_REQUEST, (char*)"13"},
	{INCOMING_CODE_READY_FOR_BALANCE_REQUEST, (char*)"14"},
};

nfc_pos_outgoing_transaction_table_entry outgoing_table [OUTGOING_CODE_MAX] =
{
	{OUTGOING_CODE_MESSAGE_ACK, (char*)"00"},
	{OUTGOING_CODE_PEER_READY_REQUEST, (char*)"01"},
	{OUTGOING_CODE_TRANSACTION_ID_RECEIVED_CONFIRMATION, (char*)"02"},
	{OUTGOING_CODE_TRY_AGAIN_REQUEST,(char*) "03"},
	{OUTGOING_CODE_READY_FOR_RECEIPT_RESPONSE, (char*)"04"},
	{OUTGOING_CODE_RECEIPT_VALID_MESSAGE, (char*)"05"},
	{OUTGOING_CODE_RECEIPT_INVALID_MESSAGE, (char*)"06"},
	{OUTGOING_CODE_READY_FOR_BALANCE_RESPONSE, (char*)"07"},
	{OUTGOING_CODE_BALANCE_RECEIVED_CONFIRMATION, (char*)"08"},
};

/*
 * Configure NFC board
 */
void nfc_pos_configure_board(void)
{
	nfc_pos_print("nfc_pos_configure_board:: Starting NFC...");
	nfc.begin();

	uint32_t versiondata = nfc.getFirmwareVersion();
	if (!versiondata)
	{
		nfc_pos_print("nfc_pos_configure_board:: Didn't find PN53x board");
		//while (1); // halt
	}
	// Got ok data, print it out!
  	Serial.print("nfc_pos_configure_board:: Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
  	Serial.print("nfc_pos_configure_board:: Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
  	Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);

	// configure board to read RFID tags and cards
	nfc.SAMConfig();
}

/*
 * Construct and send message to the mobile device
 */
nfc_pos_message_type nfc_pos_send_message_to_peer(int code, char * text, int data)
{
	//create and initialize incoming message structure
	nfc_pos_message_type received_message;
	received_message.transaction_code = INCOMING_CODE_INVALID;
	received_message.text = (char*)"";
	received_message.data = NULL;

	//buffers to hold formatted messages
	char data_in_buffer[MESSAGE_BUFFER_SIZE];
	char data_out_buffer[MESSAGE_BUFFER_SIZE];

	//format message for transfer and store in out buffer
	sprintf (data_out_buffer, "%s\n%s\n%d", outgoing_table[code].message, text, data);

	//trans-receive data
	if(nfc.inDataExchange(data_out_buffer, (uint8_t)sizeof(data_out_buffer), data_in_buffer, (uint8_t*)sizeof(data_in_buffer)))
	{
		//build structure of received message
		int count = 0;
		int text_index = 0;
		int data_index = 0;
		for(size_t i=0; i<strlen(data_out_buffer); i++ )
		{
			if(data_out_buffer[i]=='\n')
			{
				data_out_buffer[i] = '\0';
				if (count == 0)
				{
					received_message.transaction_code = (int)data_out_buffer;
					text_index = i+1;
				}
				else if (count == 1)
				{
					received_message.text = (char*)data_out_buffer[text_index];
					data_index = i+1;
				}
				else if (count == 2)
				{
					received_message.data = (int)data_out_buffer[data_index];
				}
				count ++;
			}
		}
		nfc_pos_print("nfc_pos_send_message_to_peer():: Message from peer.\nTransaction Code: %d\nText: %s\nData: %d received from peer",
				received_message.transaction_code, received_message.text, received_message.data);
	}
	else
	{
		nfc_pos_print("nfc_pos_send_message_to_peer():: nfc.inDataExchange() failed!");
	}

	return received_message;
}

/*
 * Ask the mobile device if it is ready to begin transaction
 */
boolean nfc_pos_mobile_peer_ready()
{
	nfc_pos_print("Waiting for mobile device to be ready...");
	boolean status = false;
	if (INCOMING_CODE_PEER_DEVICE_READY_RESPONSE == nfc_pos_send_message_to_peer(OUTGOING_CODE_PEER_READY_REQUEST, (char*)"Hello", 6841).transaction_code){
		status = true;
	}
	return true;
}

int nfc_pos_transact(int paymentAmount)
{
	int status = -1;
	nfc_pos_configure_board();

	nfc_pos_print("nfc_pos_transact: Entering transaction loop");
    while (true){
		 // Configure PN532 as Peer to Peer Target
		if(nfc.inListPassiveTarget()) //if connection is error-free
		{
			if (nfc_pos_mobile_peer_ready())
			{
				nfc_pos_print("Initiating payment transaction for $%d", paymentAmount);

				status = EOK;
			}
		}
		else
		{
			nfc_pos_print("Unable to configure the PN532 board as Peer to Peer target");
		}
    }
    nfc_pos_print("nfc_pos_transact: Returning to main");
	return status;
}
