/*============================================================================
 * License: 
 * Author: 
 * Date: 
 *===========================================================================*/

/*==================[inclusions]=============================================*/

#include "program.h"   // <= Own header
#include "sapi.h"      // <= sAPI library
#include "gsm.h"
#include "sim900.h"
#include "string.h"
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void console(char* msg)
{
 uartWriteString(UART_USB, msg);
 uartWriteByte( UART_USB, '\r' );
  uartWriteByte( UART_USB, '\n' );
}
void printLine(char* msg)
{
 uartWriteString(UART_USB, msg);
 
}
void leerBuffer()
{
   char buffer[STR_MAX];
    cleanBuffer(buffer,STR_MAX);
 
    readBuffer(UART_232, buffer,STR_MAX, TIMEOUT_MAX);
    printLine("Response  :");
    console(buffer);
    delay(100);

   
}

void sendAT(char* AT, int t)
{
    printLine("COMAND AT :");
  console(AT);
 uartWriteString(UART_232,AT);
  uartWriteByte( UART_232, '\r' );
  uartWriteByte( UART_232, '\n' );
  delay(t);
  //mostrar respuesta
  leerBuffer();
}

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[main function]==========================================*/

// MAIN FUNCTION, ENTRY PINT TO THE PROGRAM AFTER POR OR RESET.
int main( void ){

   // ---------- SETUP ----------------------------------------


    // Initialize an configurate the board
    boardConfig();   
    uartConfig( UART_232, 19200 );//para comandos at
    uartConfig( UART_USB, 19200 );//para 

  
    console("INICIANDO PROGRAMA");
 char URL[70] = "\"http://www.sambrana.com.ar/ciaa/rest.php\"";
 char data[30];

   // sendAT("ATD3795013243;");
// EnviaSMS(UART_232, "HOLA CIAA","3794735197" );
  // callNumber(UART_232,"3794601885");
// delay(3000);
    //Configuración APN
//Esta configuración 1 vez al principio
  sendAT("AT",1000);
    sendAT("AT+CPIN?",1000);
    sendAT("AT+CREG=1",1000);
// See if the SIM900 is ready
  sendAT("AT",1000);
  
  

  // SIM card inserted and unlocked?
  sendAT("AT+CPIN?",1000);
  
  

  // Is the SIM card registered?
  sendAT("AT+CREG?",1000);
  
  

  // Is GPRS attached?
  sendAT("AT+CGATT?",1000);
  
  

  // Check signal strength
  sendAT("AT+CSQ ",1000);
  
  
  sendAT("AT+HTTPTERM",300);
  // Set connection type to GPRS
  sendAT("AT+SAPBR=3,1,\"Contype\",\"GPRS\"",2000);
  
  

  // Set the APN
  // APN PARA CLARO
  sendAT("AT+SAPBR=3,1,\"APN\",\"igprs.claro.com.ar\"",2000);


  // Enable GPRS
  sendAT("AT+SAPBR=1,1",10000);
  
  

  // Check to see if connection is correct and get your IP address
  sendAT("AT+SAPBR=2,1",2000);
  
 

  while( TRUE )
   { 
    
 // // ---------- REPEAT FOR EVER ------------------------------
  
    //inicio conexion
    sendAT("AT+HTTPINIT",2000);
 
     sendAT("AT+HTTPPARA=\"CID\",1",2000);
   // set http param value
   // ToDO : send dynamic value
 
    //HOST: www.sambrana.com.ar
    // METHOD GET: user = ciaa & data=sim900
     sendAT("AT+HTTPPARA=\"URL\",\"http://www.linsse.com.ar/ciaa/rest.php?user=ciaa&data=sim900_test\"",4000);


   // set http action type 0 = GET, 1 = POST, 2 = HEAD
   sendAT("AT+HTTPACTION=0",6000);


   // read server response
   sendAT("AT+HTTPREAD",1000); 


   //cierro conexion
   sendAT("AT+HTTPTERM",300);
    delay(1000);

   } 
   // IT SHOULD NEVER COME HERE, because this program runs directly on a
   // microcontroller and is not called by any Operating System, as in
   // case of a PC program.
   return 0;
}

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*==================[end of file]============================================*/
