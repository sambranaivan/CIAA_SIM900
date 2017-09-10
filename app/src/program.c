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
/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

/*==================[internal functions declaration]=========================*/
void console(char* msg)
{
 uartWriteString(UART_USB, msg);
 uartWriteByte( UART_232, '\r' );
  uartWriteByte( UART_232, '\n' );
}

void sendAT(char* AT)
{
 uartWriteString(UART_232,AT);
  uartWriteByte( UART_232, '\r' );
  uartWriteByte( UART_232, '\n' );
}

void leerBuffer(char *buffer)
{
  cleanBuffer(buffer,70);
    readBuffer(UART_232, buffer,STR_MAX, TIMEOUT_MAX);
    console(buffer);
}
/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[main function]==========================================*/

// MAIN FUNCTION, ENTRY PINT TO THE PROGRAM AFTER POR OR RESET.
int main( void ){

   // ---------- SETUP ----------------------------------------
  char buffer[70];//buffer de lectura de puerto serial
 
   // Initialize an configurate the board
   boardConfig();   
   uartConfig( UART_232, 19200 );//para comandos at
   uartConfig( UART_USB, 19200 );//para 
    
    console("INICIANDO PROGRAMA");
    sendAT("AT");
    delay(100);
    leerBuffer(buffer);
    
    
    sendAT("AT+CPIN?");
    delay(100);
    
   leerBuffer(buffer);
    sendAT("AT+CREG=1");
 delay(100);
    
   leerBuffer(buffer);
    
    sendAT("ATD3795013243;");

    delay(30000);
    
    leerBuffer(buffer);

   
    
   // // ---------- REPEAT FOR EVER ------------------------------
   while( TRUE )
   {
       
      // If TEC1 is pressed, turn on the LEDR
      gpioWrite( LEDR, !(gpioRead(TEC1)) );
       gpioWrite( LEDG, !(gpioRead(TEC1)) );
       gpioWrite( LEDB, !(gpioRead(TEC1)) );
      
      // If TEC2 is pressed, turn on the LED1
      gpioWrite( LED1, !(gpioRead(TEC2)) );
      
      // If TEC3 is pressed, turn on the LED2
      gpioWrite( LED2, !(gpioRead(TEC3)) );
      
      // If TEC4 is pressed, turn on the LED3
      gpioWrite( LED3, !(gpioRead(TEC4)) );

      // Toggle LEDB
      gpioToggle( LEDB );
      
      // Blocking delay for 100ms
      delay( 100 );
   } 

   // IT SHOULD NEVER COME HERE, because this program runs directly on a
   // microcontroller and is not called by any Operating System, as in
   // case of a PC program.
   return 0;
}

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*==================[end of file]============================================*/
