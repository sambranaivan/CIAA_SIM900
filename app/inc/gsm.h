#ifndef _GSM_H_
#define _GSM_H_

/*==================[inclusions]=============================================*/

#include "sapi.h"
#include "stdlib.h"
#include "ctype.h"

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

#define STR_MAX 200
#define NUM_MAX 25
#define TIMEOUT_MAX 3000
#define MAX_MSGS 5
#define RESET_PIN GPIO8

/*==================[typedef]================================================*/

/*==================[external data declaration]==============================*/

/*==================[external functions declaration]=========================*/
void EnviaSMS(uartMap_t uart, char* msg,char* phone_number);
bool_t ReadString(uartMap_t uart, char *str);
bool_t LeerSMS(uartMap_t uart, uint8_t index, char *str);
void cleanBuffer(char *buffer, int count);
int readBuffer(uartMap_t uart, char *buffer,int count, tick_t timeOut);
void  callNumber(uartMap_t uart, char* number);
bool_t hangoffCall(uartMap_t uart);
bool_t getNumberSMS(char *str, char *number);
bool_t getMsgSMS(char *str, char *msg);
bool_t delAllSms(uartMap_t uart);
void deleteSMS(uartMap_t uart, int index);
void signalQuality(uartMap_t uart,char *sgnQ);
void gsm_reset(uartMap_t uart);

char* itoa(int value, char* result, int base);

/*==================[cplusplus]==============================================*/

#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* #ifndef _GSM_H_ */
