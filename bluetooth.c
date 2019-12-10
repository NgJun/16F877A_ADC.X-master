#include "bluetooth.h"

void Initialize_Bluetooth()    
{
   //Set the pins of RX and TX//
    TRISC6=1;
    TRISC7=1;
    
    //Set the baud rate using the look up table in datasheet(pg114)//
    // Baud rate cua hau het c�c bluetooth module l� 9600
    BRGH=1;      //BRGH enabled : high speed, baud rate ( B?t bu?c)
    SPBRG  =129;    // Tra bang BaudRate = 9600 v� FREQ = 20MHz th� SPBRG = 129
    
    //Turn on Asyc. Serial Port//
    /*
     * SYNC: USART Mode Select bit
     * 1 = Synchronous mode
     * 0 = Asynchronous mode
     */
    SYNC=0;
    SPEN=1;
    
    //Set 8-bit reception and transmission
    /*
     * TX9: 9-bit Transmit Enable bit
     * 1 = Selects 9-bit transmission/reception
     * 0 = Selects 8-bit transmission/reception
     */
    RX9=0;
    TX9=0;
    
    TXEN=1;  // Enable transmit
    CREN=1; //Enable Continuous Receive
    
    //Enable global and ph. interrupts//
    GIE = 1;
    PEIE= 1;
  
    //Enable interrupts for Tx. and Rx.//
    RCIE=1;
    TXIE=1;
}
    
void BT_load_char(char byte)
{
    while(TXIF==0); // Doi den khi register transmitter trong   
    while(TRMT==0);// Doi den khi Trans Shift Reg trong
    TXREG = byte; // Load char need to send to reg of  trans
}

void BT_load_string(char* string)
{
    while(*string)  BT_load_char(*string++);  
    
}
void broadcast_BT()
{
  TXREG = 13;  
  //__delay_ms(blt_delay);
}
char BT_get_char(void)
{
    if(OERR) // check for over run error 
    {
        CREN = 0;
        CREN = 1; //Reset CREN
    }
    
    if(RCIF==1) //if the user has sent a char return the char (ASCII value)
    {
    while(!RCIF);     // Wait till the data is received 
    return RCREG;
    }
    else //if user has sent no message return 0
        return 0;
}
