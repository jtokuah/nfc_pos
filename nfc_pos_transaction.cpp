#include <Adafruit_NFCShield_I2C.h> //NFC library
#include <Wire.h>
#include <errno.h>
#include "nfc_pos.h"
#include "nfc_pos_transaction.h"

#ifdef nfc


Adafruit_NFCShield_I2C nfc(IRQ, RESET);

/*This table maps the outgoing message codes strings to the corresponding
 *  internal enumerated type
 */
nfc_pos_outgoing_transaction_table_entry outgoing_table [OUT_CODE_MAX] =
{
	{OUT_CODE_MESSAGE_ACK, (char*)"00"},
	{OUT_CODE_PEER_READY_REQ, (char*)"01"},
	{OUT_CODE_TRANSACTION_ID_RECEIVED_CONF, (char*)"02"},
	{OUT_CODE_TRY_AGAIN_REQ,(char*) "03"},
	{OUT_CODE_READY_FOR_RECEIPT_RESP, (char*)"04"},
	{OUT_CODE_RECEIPT_VALID_MESSAGE, (char*)"05"},
	{OUT_CODE_RECEIPT_INVALID_MESSAGE, (char*)"06"},
	{OUT_CODE_READY_FOR_BALANCE_RESP, (char*)"07"},
	{OUT_CODE_BALANCE_RECEIVED_CONF, (char*)"08"},
	{OUT_CODE_SENDING_PAYMENT_AMOUNT, (char*)"09"},
};

/*
 * This function configures the NFC board
 */
void nfc_pos_configure_board(void)
{
	progmemPrintln(PSTR("\nnfc_pos_configure_board():: Starting NFC..."));
	nfc.begin();

	uint32_t versiondata = nfc.getFirmwareVersion();
	if (!versiondata)
	{
		Serial.println("\nDidn't find PN53x board");
		while (1); // halt
	}
	// Got ok data, print it out!
  	Serial.print("\nFound chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX);
  	Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC);
  	Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
	// configure board to read RFID tags and cards
	nfc.SAMConfig();
}

/*
 * This function exchanges messages with the mobile device. It returns the response
 * message received from the mobile device.
 */
nfc_pos_message_type nfc_pos_message_mobile(int code, char * text, int data)
{
	//create and initialize incoming message structure
	nfc_pos_message_type received_message;
	received_message.transaction_code = IN_MESSAGE_NOT_SENT;
	received_message.text = (char*)"";
	received_message.data = -1;

	//buffers to hold formatted messages
	char data_in_buffer[MESSAGE_BUFFER_SIZE];
	char data_out_buffer[MESSAGE_BUFFER_SIZE];

	//format message for transfer and store in out buffer. '!' is used to separate the different message components
	sprintf (data_out_buffer, "%s!%s!%d", outgoing_table[code].message, text, data);

	//trans-receive data
	if(nfc.inDataExchange(data_out_buffer, (uint8_t)sizeof(data_out_buffer), data_in_buffer, (uint8_t*)sizeof(data_in_buffer)))
	{
		//build structure of received message
		int count = 0;
		int text_index = 0;
		int data_index = 0;
		for(size_t i=0; i<strlen(data_out_buffer); i++ )
		{
			if(data_out_buffer[i]=='!')
			{
				data_out_buffer[i] = '\0';
				if (count == 0 )
				{
					if ((strcmp(data_out_buffer, "!")!=0))
					{
						received_message.transaction_code = (int)data_out_buffer;
						text_index = i+1;
					}
					else
					{
						received_message.transaction_code = IN_CODE_INVALID;
						text_index = i+2;
					}
				}
				else if (count == 1)
				{
					if (data_out_buffer[text_index] != '!')
					{
						received_message.text = (char*)data_out_buffer[text_index];
						data_index = i+1;
					}
					else
					{
						data_index = i+2;
					}
				}
				else if (count == 2)
				{
					received_message.data = (int)data_out_buffer[data_index];
				}
				count ++;
			}
		}

		//Print contents of the message
		progmemPrintln(PSTR("\nnfc_pos_send_message_to_peer():: Message from mobile peer."));
		progmemPrint(PSTR("Transaction Code: "));Serial.println(data_out_buffer);
		progmemPrint(PSTR("Text: "));Serial.println(data_out_buffer[text_index]);
		progmemPrint(PSTR("Data: "));Serial.println(data_out_buffer[data_index]);
		progmemPrint(PSTR("\n"));
	}
	else
	{
		progmemPrintln(PSTR("\nnfc_pos_send_message_to_peer():: nfc.inDataExchange() failed!\n"));
	}

	return received_message;
}

/*
 * This function asks the mobile device if it is ready to begin transaction by exchanges messages
 */
boolean nfc_pos_mobile_peer_ready()
{
	boolean status = false;
	nfc_pos_message_type received_message;

	progmemPrintln(PSTR("\nnfc_pos_mobile_peer_ready():: Waiting for mobile device to be ready...\n"));

	//exchange message with mobile device
	received_message = nfc_pos_message_mobile(OUT_CODE_PEER_READY_REQ, "" ,NULL);
	if (received_message.transaction_code == IN_CODE_PEER_DEVICE_READY_RESP)
	{
		status = true;
	}
	//return status;
	return true; //JT:HACK
}

/*
 * This function returns an error description for the specified error code
 */
char* nfc_pos_transaction_error(nfc_pos_transaction_error_code_type err_no)
{
	char* error = (char*)"";

	return error;
}
/*
 * This is the main function that handles the payment transaction protocols
 *
 */
nfc_pos_transaction_result_type nfc_pos_transaction_handler(int paymentAmount, char* accountNum)
{
	int num_tries = 0;
	nfc_pos_transaction_error_code_type error_code = ERR_NO_ERROR;
	nfc_pos_message_type received_message;
	nfc_pos_transaction_result_type result;
	result.status = -1;
	result.transaction_ID = -1;
	result.receipt_num = -1;

	progmemPrintln(PSTR("\nnfc_pos_transaction_handler():: Entering transaction loop...\n"));
	while ((result.status != EOK) && (num_tries <= MAX_NUM_TRANSACTION_RETRIES)){
		num_tries++;
		 // Configure PN532 as Peer to Peer Target
		if(nfc.inListPassiveTarget()) //if connection is error-free
		{
			if (nfc_pos_mobile_peer_ready())
			{
				progmemPrint(PSTR("nfc_pos_transaction_handler():: Initiating payment transaction for $"));
				Serial.println((char*)paymentAmount);

				//send the payment amount to the mobile
				progmemPrint(PSTR("nfc_pos_transaction_handler():: Sending payment amount"));
				received_message = nfc_pos_message_mobile(OUT_CODE_SENDING_PAYMENT_AMOUNT, "", paymentAmount);
				switch (received_message.transaction_code)
				{
					case IN_CODE_PAYMENT_AMOUNT_RECEIVED_CONF:
						break;
					case IN_CODE_PAYMENT_AMOUNT_INVALID:
					case IN_CODE_INVALID:
						error_code = ERR_PAYMENT_AMOUNT_NOT_SENT;
						break;
					case IN_MESSAGE_NOT_SENT:
						error_code = ERR_MESSAGE_NOT_SENT;
						break;
					default:
						error_code = ERR_UNKNOWN;
						break;
				}

				//send the merchant's account number to the mobile
				if (error_code == ERR_NO_ERROR)
				{
					received_message = nfc_pos_message_mobile(OUT_CODE_SENDING_MERCHANT_ACCT_NUM, accountNum, NULL);
					switch (received_message.transaction_code)
					{
						case IN_CODE_ACCT_NUM_RECEIVED_CONF:
							break;
						case IN_CODE_ACCT_NUM_INVALID:
		                    error_code = ERR_ACCT_NUM_INVALID;
							break;
						case IN_CODE_INVALID:
							error_code = ERR_ACCT_NUM_NOT_SENT;
							break;
						case IN_MESSAGE_NOT_SENT:
							error_code = ERR_MESSAGE_NOT_SENT;
							break;
						default:
							error_code = ERR_UNKNOWN;
							break;
					}
				}

				//persistently check server connection status
				while ((error_code == ERR_NO_ERROR) || (error_code == ERR_UNDETERMINED))
				{
					if (error_code == ERR_NO_ERROR) displayLine("Contacting server...");
					received_message = nfc_pos_message_mobile(OUT_CODE_SERVER_CONNECTION_STATUS_REQ, "", NULL);
					switch (received_message.transaction_code)
					{
						case IN_CODE_SERVER_CONNECTION_SUCCESS:
							error_code = ERR_NO_ERROR;
							result.transaction_ID = received_message.data;
							break;
						case IN_CODE_CONNECTING_TO_SERVER:
							error_code = ERR_UNDETERMINED;
							break;
						case IN_CODE_SERVER_CONNECTION_FAILED:
						case IN_CODE_INVALID:
							error_code = ERR_SERVER_CONNECTION_FAILED;
							break;
						case IN_MESSAGE_NOT_SENT:
							error_code = ERR_MESSAGE_NOT_SENT;
							break;
						default:
							error_code = ERR_UNKNOWN;
							break;
					}
				}

				//persistently check authentication status
				while ((error_code == ERR_NO_ERROR) || (error_code == ERR_UNDETERMINED))
				{
					if (error_code == ERR_NO_ERROR) displayLine("Authenticating...");
					received_message = nfc_pos_message_mobile(OUT_CODE_AUTH_STATUS_REQ, "", NULL);
					switch (received_message.transaction_code)
					{
						case IN_CODE_AUTHENTICATION_SUCCESS:
							error_code = ERR_NO_ERROR;
							break;
						case IN_CODE_AUTHENTICATING:
							error_code = ERR_UNDETERMINED;
							break;
						case IN_CODE_AUTHENTICATION_FAILED:
						case IN_CODE_INVALID:
							error_code = ERR_AUTHENTICATION_FAILED;
							break;
						case IN_MESSAGE_NOT_SENT:
							error_code = ERR_MESSAGE_NOT_SENT;
							break;
						default:
							error_code = ERR_UNKNOWN;
							break;
					}
				}

				//persistently check verification status
				while ((error_code == ERR_NO_ERROR) || (error_code == ERR_UNDETERMINED))
				{
					if (error_code == ERR_NO_ERROR) displayLine("Verifying payment...");
					/*
					 * 'received_message.text': contains part of the message from the server (normally
					 *                          the reason for the transaction failure.
					 * 'received_message.data': contains the remaining length of the remaining part of the
					 *                          message still to be received.
					 */
					received_message = nfc_pos_message_mobile(OUT_CODE_VERIFICATION_STATUS_REQ, "", received_message.data);
					switch (received_message.transaction_code)
					{
						case IN_CODE_TRANSACTION_SUCCESS:
							error_code = ERR_NO_ERROR;
							break;
						case IN_CODE_VERIFYING:
							error_code = ERR_UNDETERMINED;
							break;
						case IN_CODE_TRANSACTION_FAILED:
							if (received_message.data != 0)
							{
								strlcat(result.server_message, received_message.text, sizeof(result.server_message));
								error_code = ERR_UNDETERMINED;
							}
							else
							{
								error_code = ERR_TRANSACTION_FAILED;
							}
							break;
						case IN_CODE_INVALID:
							error_code = ERR_TRANSACTION_FAILED;
							break;
						case IN_MESSAGE_NOT_SENT:
							error_code = ERR_MESSAGE_NOT_SENT;
							break;
						default:
							error_code = ERR_UNKNOWN;
							break;
					}
				}
			}
		}
		else
		{
			progmemPrintln(PSTR("\nnfc_pos_transaction_handler():: Unable to list the PN532 as passive target"));
		}
		if (num_tries != MAX_NUM_TRANSACTION_RETRIES) error_code = ERR_NO_ERROR;
		else if (error_code == ERR_NO_ERROR) result.status = EOK;
    }
	if (error_code != ERR_NO_ERROR)
	{
		progmemPrint(PSTR("nfc_pos_transaction_handler():: Transaction failed with error :"));
		Serial.println(nfc_pos_transaction_error(error_code));
	}
    progmemPrintln(PSTR("nfc_pos_transaction_handler():: Returning to main"));
	return result;
}

#endif