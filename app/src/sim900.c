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