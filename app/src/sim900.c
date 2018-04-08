#include "gsm.h"
#include "sapi.h"
#include "string.h"

void simSetup()
{
    uartWriteString(UART_232, "AT");
    uartWriteByte( UART_232, '\r' );
	uartWriteByte( UART_232, '\n' );
    delay(1000);
        
    uartWriteString(UART_232, "AT+CPIN?");
     uartWriteByte( UART_232, '\r' );
	uartWriteByte( UART_232, '\n' );
    delay(1000);
    
    
    uartWriteString(UART_232, "AT+CREG=1");
    uartWriteByte( UART_232, '\r' );
	uartWriteByte( UART_232, '\n' );
    delay(1000);
    }
void EnviaSMS(uartMap_t uart, char* msg,char* phone_number ){


	const char* str1="AT+CMGS=\"";
	const char* str2="\"";
	char str_n[50];


	strcpy(str_n,str1);
	strcat(str_n,phone_number);
	strcat(str_n,str2);
//	sprintf(str_n,"AT+CMGS=\"%s\"\r\n", phone_number);

	uartWriteString(uart, "AT+CMGF=1");        					// Activamos la funcion de envio de SMS
	uartWriteByte( uart, '\r' ); 								/* Envía '\r', retorno de carro */
	uartWriteByte( uart, '\n' );
	delay(100);                                    					// Pequeña pausa
	uartWriteString(uart, str_n);  								// Definimos el numero del destinatario en formato internacional
	uartWriteByte( uart, '\r' ); 								/* Envía '\r', retorno de carro */
	uartWriteByte( uart, '\n' );
	delay(100);                                    					// Pequeña pausa
	uartWriteString(uart, msg);                 				// Definimos el cuerpo del mensaje
	delay(500);                                    					// Pequeña pausa
	uartWriteByte(uart, 26);                      				// Enviamos el equivalente a Control+Z
	delay(100);                                    					// Pequeña pausa
	uartWriteByte( uart, '\r' ); 								/* Envía '\r', retorno de carro */
	uartWriteByte( uart, '\n' ); 								/* Envía '\n', nueva línea      */
	delay(100);                                    					// Pequeña pausa
}



bool_t LeerSMS(uartMap_t uart, uint8_t index, char *str){

	char str_aux[STR_MAX];
	const char* str1="AT+CMGR=";
	char str_n[50];
	char index_str[10];


//	sprintf(str_n,"AT+CMGR=%d",index);
	itoa( index, index_str, 10 );
	strcpy(str_n,str1);
	strcat(str_n,index_str);

	uartWriteString(uart, "AT+CMGF=1");
	uartWriteByte( uart, '\r' );
	uartWriteByte( uart, '\n' );
	delay(100);
	ReadString(uart, str_aux);

	if(strstr(str_aux,"ER")==NULL){

		uartWriteString(uart, str_n);
		uartWriteByte( uart, '\r' );
		uartWriteByte( uart, '\n' );
		cleanBuffer(str_aux,STR_MAX);
		readBuffer(uart, str_aux,STR_MAX,TIMEOUT_MAX);

		if(strstr(str_aux,"CMGR:")!=NULL){

			strcpy(str,str_aux);
			return TRUE;
		}
		else return FALSE;

	}
	else return FALSE;

}

void  callNumber(uartMap_t uart, char* number){

	uartWriteString(uart, "ATD");
	uartWriteString(uart, number);
	uartWriteByte( uart, ';' );
	uartWriteByte( uart, '\r' );
	uartWriteByte( uart, '\n' );
}

bool_t hangoffCall(uartMap_t uart){

	char str_aux[100]={0};

	uartWriteString(uart, "ATH\r\n");
	readBuffer(uart, str_aux,STR_MAX,TIMEOUT_MAX);

	if ( strstr(str_aux,"OK") != NULL) return TRUE;
	else return FALSE;
}

bool_t getNumberSMS(char *str, char *number){

	size_t i,k;

	for(i=0,k=0;(k<5) && (i<STR_MAX);i++){

		if(isdigit(str[i])) k++;
		else k=0;
	}

	if(i<100) i-=5;
	else return FALSE;

	cleanBuffer(number,NUM_MAX);

	for(k=0;(str[i]!='\"')&&(i<STR_MAX);k++,i++)

		number[k]=str[i];

	if(i<STR_MAX) return TRUE;
	else return FALSE;

}

bool_t getMsgSMS(char *str, char *msg){

	char *ptr;
	size_t i;

	if((ptr=strstr(str,"CMGR:"))==NULL) return FALSE;

	if((ptr=strchr(ptr,10))==NULL) return FALSE;		//Busca el end of line (/n, char 10)

	ptr++;

	for(i=0;(*ptr!=10)&&(*ptr!=13)&&(i<STR_MAX);i++) ptr++;			//Hasta el end of line (/n, char 10) o CR(\r, char 13)

	ptr-=i;

	cleanBuffer(msg,STR_MAX);

	strncpy(msg,ptr,i);

	return TRUE;

}

void deleteSMS(uartMap_t uart, int index)
{
	const char* str1="AT+CMGD=";
	char str_n[50];
	char index_str[10];

	itoa( index, index_str, 10 );
	strcpy(str_n,str1);
	strcat(str_n,index_str);


//    snprintf(cmd,sizeof(cmd),"AT+CMGD=%d\r\n",index);

	uartWriteString(uart, str_n);
	uartWriteByte( uart, '\r' );
	uartWriteByte( uart, '\n' );

}

bool_t delAllSms(uartMap_t uart){

	char str_aux[100]={0};

	uartWriteString(uart, "at+cmgda=\"del all\"\n\r");
	readBuffer(uart, str_aux,STR_MAX,TIMEOUT_MAX);

	if ( strstr(str_aux,"OK") != NULL) return TRUE;
		else return FALSE;

}