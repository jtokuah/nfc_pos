 /*
 * nfc_pos_transaction.h
 *
 *  Created on: Aug 10, 2013
 *      Author: jefferson
 */

#ifndef NFC_POS_TRANSACTION_H_
#define NFC_POS_TRANSACTION_H_

/* --- Symbolic names of the error return conditions --- */
#define EOK          	0  /* No error                             	*/
#define EPROTO      	1  /* Protocol error                       	*/
#define EBADRQC     	2  /* Invalid request code                 	*/

#define MESSAGE_BUFFER_SIZE 			16
#define MAX_NUM_TRANSACTION_RETRIES		3

typedef enum{
	INCOMING_CODE_INVALID = -1,
	INCOMING_CODE_MESSAGE_ACK = 0,
	INCOMING_CODE_PEER_DEVICE_READY_RESPONSE = 1,
	INCOMING_CODE_PAYMENT_AMOUNT_RECEIVED_CONFIRMATION = 2,
	INCOMING_CODE_MERCHANT_ACCT_NUM_RECEIVED_CONFIRMATION = 3,
    INCOMING_CODE_SERVER_CONNECTION_SUCCESSFUL = 4,
    INCOMING_CODE_SERVER_CONNECTION_FAILED = 5,
    INCOMING_CODE_MERCHANT_AUTHENTICATION_SUCCESSFUL = 6,
    INCOMING_CODE_MERCHANT_AUTHENTICATION_FAILED = 7,
    INCOMING_CODE_CUSTOMER_AUTHENTICATION_SUCCESSFUL = 8,
    INCOMING_CODE_CUSTOMER_AUTHENTICATION_FAILED = 9,
    INCOMING_CODE_INSUFFICIENT_FUNDS_RESULT = 10,
    INCOMING_CODE_TRANSACTION_SUCCESSFUL = 11,
    INCOMING_CODE_TRANSACTION_FAILED = 12,
    INCOMING_CODE_READY_FOR_RECEPT_REQUEST = 13,
    INCOMING_CODE_READY_FOR_BALANCE_REQUEST = 14,
    INCOMING_CODE_MAX
}nfc_pos_transaction_code_incoming_type;

typedef enum{
	OUTGOING_CODE_INVALID = -1,
	OUTGOING_CODE_MESSAGE_ACK = 0,
	OUTGOING_CODE_PEER_READY_REQUEST = 1,
	OUTGOING_CODE_TRANSACTION_ID_RECEIVED_CONFIRMATION = 2,
	OUTGOING_CODE_TRY_AGAIN_REQUEST = 3,
	OUTGOING_CODE_READY_FOR_RECEIPT_RESPONSE = 4,
	OUTGOING_CODE_RECEIPT_VALID_MESSAGE = 5,
	OUTGOING_CODE_RECEIPT_INVALID_MESSAGE = 6,
	OUTGOING_CODE_READY_FOR_BALANCE_RESPONSE = 7,
	OUTGOING_CODE_BALANCE_RECEIVED_CONFIRMATION = 8,
	OUTGOING_CODE_SENDING_PAYMENT_AMOUNT = 9,
	OUTGOING_CODE_MAX
}nfc_pos_transaction_code_outgoing_type;

typedef struct {
	nfc_pos_transaction_code_incoming_type code;
	char* message;
}nfc_pos_incoming_transaction_table_entry;

typedef struct {
	nfc_pos_transaction_code_outgoing_type code;
	char* message;
}nfc_pos_outgoing_transaction_table_entry;

typedef struct nfc_pos_message_type{
	int transaction_code;
	char* text;
	int data;
}nfc_pos_message_type;



#endif /* NFC_POS_TRANSACTION_H_ */
