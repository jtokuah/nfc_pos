 /*
 * nfc_pos_transaction.h
 *
 *  Created on: Aug 10, 2013
 *      Author: jefferson
 */

#ifndef NFC_POS_TRANSACTION_H_
#define NFC_POS_TRANSACTION_H_

/* Symbolic names of the error return conditions */
#define EOK          	0  /* No error                             	*/
#define EPROTO      	1  /* Protocol error                       	*/
#define EBADRQC     	2  /* Invalid request code                 	*/

#define MESSAGE_BUFFER_SIZE 			16
#define MAX_NUM_TRANSACTION_RETRIES		3

/* Incoming transaction message codes send to the mobile device */
typedef enum{
	IN_CODE_INVALID = -1,
	IN_CODE_MESSAGE_ACK = 0,
	IN_CODE_PEER_DEVICE_READY_RESP = 1,
	IN_CODE_PAYMENT_AMOUNT_RECEIVED_CONF = 2,
	IN_CODE_ACCT_NUM_RECEIVED_CONF = 3,
    IN_CODE_SERVER_CONNECTION_SUCCESS = 4,
    IN_CODE_SERVER_CONNECTION_FAILED = 5,
    IN_CODE_AUTHENTICATION_SUCCESS = 6,
    IN_CODE_AUTHENTICATION_FAILED = 7,
    IN_CODE_INSUFF_FUNDS_RESULT = 8,
    IN_CODE_TRANSACTION_SUCCESS = 9,
    IN_CODE_TRANSACTION_FAILED = 10,
    IN_CODE_VERIFYING = 11,
    IN_CODE_READY_FOR_BALANCE_REQ = 12,
    IN_CODE_PAYMENT_AMOUNT_INVALID = 13,
    IN_CODE_ACCT_NUM_INVALID = 14,
    IN_CODE_CONNECTING_TO_SERVER = 15,
    IN_CODE_AUTHENTICATING = 16,
    IN_MESSAGE_NOT_SENT = 17,
    //all new codes should be placed above this line
    IN_CODE_MAX
}nfc_pos_transaction_code_incoming_type;

/* Incoming transaction message codes receive from the mobile device */
typedef enum{
	OUT_CODE_INVALID = -1,
	OUT_CODE_MESSAGE_ACK = 0,
	OUT_CODE_PEER_READY_REQ = 1,
	OUT_CODE_TRANSACTION_ID_RECEIVED_CONF = 2,
	OUT_CODE_TRY_AGAIN_REQ = 3,
	OUT_CODE_READY_FOR_RECEIPT_RESP = 4,
	OUT_CODE_RECEIPT_VALID_MESSAGE = 5,
	OUT_CODE_RECEIPT_INVALID_MESSAGE = 6,
	OUT_CODE_READY_FOR_BALANCE_RESP = 7,
	OUT_CODE_BALANCE_RECEIVED_CONF = 8,
	OUT_CODE_SENDING_PAYMENT_AMOUNT = 9,
	OUT_CODE_SENDING_MERCHANT_ACCT_NUM = 10,
	OUT_CODE_SERVER_CONNECTION_STATUS_REQ = 11,
	OUT_CODE_AUTH_STATUS_REQ = 12,
	OUT_CODE_VERIFICATION_STATUS_REQ = 13,
	//all new codes should be placed above this line
	OUT_CODE_MAX
}nfc_pos_transaction_code_outgoing_type;

/* Internal transaction error codes */
typedef enum{
	ERR_NO_ERROR = 0,
	ERR_UNDETERMINED,
	ERR_UNKNOWN,
	ERR_MESSAGE_NOT_SENT,
	ERR_PAYMENT_AMOUNT_NOT_SENT,
	ERR_ACCT_NUM_NOT_SENT,
	ERR_ACCT_NUM_INVALID,
	ERR_SERVER_CONNECTION_FAILED,
	ERR_AUTHENTICATION_FAILED,
	ERR_TRANSACTION_SUCCESS,
	ERR_TRANSACTION_FAILED,
}nfc_pos_transaction_error_code_type;

/*table structure to map the outgoing message code strings to the corresponding
 * internal enumerated type
 */
typedef struct {
	nfc_pos_transaction_code_outgoing_type code;
	char* message;
}nfc_pos_outgoing_transaction_table_entry;

/* Structure of messages exchanged with the mobile device */
typedef struct nfc_pos_message_type{
	int transaction_code;
	char* text;
	int data;
}nfc_pos_message_type;

#endif /* NFC_POS_TRANSACTION_H_ */
