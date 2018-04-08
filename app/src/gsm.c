

/*==================[inclusions]=============================================*/

#include "gsm.h"
#include "sapi.h"
#include "string.h"

/*==================[macros]=================================================*/


/*==================[typedef]================================================*/

/*==================[internal functions declaration]=========================*/

/*==================[internal functions definition]==========================*/

/*==================[external data declaration]==============================*/

volatile tick_t tickRateMS;

/*==================[external functions declaration]=========================*/

bool_t ReadString(uartMap_t uart, char *str){

	size_t i=0,k=0;
	uint8_t dato;
	bool_t retVal = TRUE;

	while((k<1000) && (i<STR_MAX)){

		if(  uartReadByte( uart, &dato ) ){

			str[i]=dato;
			i++;

		}
		k++;
	//	else break;

	}

	if(i==0) retVal=FALSE;

	return retVal;

}

void cleanBuffer(char *buffer, int count){

	int i;

	for(i=0; i < count; i++) {

		buffer[i] = '\0';
	}
}

int readBuffer(uartMap_t uart, char *buffer,int count, tick_t timeOut)
{
    int i = 0;
    uint8_t c;
    tick_t timerStart,timerEnd;

    timerStart = tickRead();
    while(1) {
        while (uartReadByte(uart, &c)==TRUE) {
//            if (c == '\r' || c == '\n') c = '$';
            buffer[i++] = c;
            if(i > count-1)break;
        }
        if(i > count-1)break;
        timerEnd = tickRead();
        if(timerEnd - timerStart > timeOut/tickRateMS) {
            break;
        }
    }
    delay(500);
    while(uartReadByte(uart, &c)==TRUE);  // display the other thing..

    return 0;
}



char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}

void signalQuality(uartMap_t uart,char *sgnQ){
/*Response
+CSQ: <rssi>,<ber>Parameters
<rssi>
0 -115 dBm or less
1 -111 dBm
2...30 -110... -54 dBm
31 -52 dBm or greater
99 not known or not detectable
<ber> (in percent):
0...7 As RXQUAL values in the table in GSM 05.08 [20]
subclause 7.2.4
99 Not known or not detectable
*/
	char str_aux[STR_MAX];
	size_t i,k;

	uartWriteString(uart,"AT+CSQ\r\n");
	cleanBuffer(str_aux,STR_MAX);
	readBuffer(uart, str_aux,STR_MAX,TIMEOUT_MAX);

	for(i=0,k=0;(str_aux[i]!=',') && (i<STR_MAX);i++){

		if(isdigit(str_aux[i])){

			sgnQ[k]=str_aux[i];
			k++;
		}

	}

//	uartWriteString(UART_USB,str_aux);
}

void gsm_reset(uartMap_t uart){

	char str_aux[STR_MAX]={0};

	gpioConfig(RESET_PIN, GPIO_OUTPUT);
	gpioWrite(RESET_PIN,HIGH);
	delay(1000);
	gpioWrite(RESET_PIN,LOW);
	delay(10000);
  // wait for the module response

/*	uartWriteString(uart,"AT\r\n");
	cleanBuffer(str_aux,STR_MAX);
	readBuffer(uart, str_aux,STR_MAX,TIMEOUT_MAX);

	while (strstr(str_aux,"OK")==NULL ){

		uartWriteString(uart,"AT\r\n");
		cleanBuffer(str_aux,STR_MAX);
		readBuffer(uart, str_aux,STR_MAX,TIMEOUT_MAX);

	}*/

  //wait for sms ready
/*	while (strstr(str_aux,"SMS")==NULL){

		cleanBuffer(str_aux,STR_MAX);
		readBuffer(uart, str_aux,STR_MAX,TIMEOUT_MAX);
	}*/

}
