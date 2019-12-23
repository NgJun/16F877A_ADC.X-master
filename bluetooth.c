#include "bluetooth.h"

void Initialize_Bluetooth()    
{
     /*
     * Set the pins of RX and TX//
    *set TX is input hence in order to transmit data we have to load the Rx buffer of BT and then broadcast it using carriage return
    *
    * The Bluetooth module has a Transmit and Receive buffer inside it, the data sent to it will be stored in the Tx buffer. 
     * This data will not be broadcasted (sent on air) unless a carriage return is sent to the module.
     */
    TRISC6=1;    
    TRISC7=1;
    
    //Set the baud rate using the look up table in datasheet(pg114)//
    // Baud rate cua hau het các bluetooth module là 9600
    
    BRGH=1;      //BRGH enabled : high speed, baud rate ( B?t bu?c)
    SPBRG  =129;    // Tra bang BaudRate = 9600 và FREQ = 20MHz thì SPBRG = 129
    
    //Turn on Asyc. Serial Port//
    /*
     * SYNC: USART Mode Select bit
     * 1 = Synchronous mode, Sync in master mode: half duplex
     * 0 = Asynchronous mode = full duplex
     * In asSync mode, it just send data signal only, without clock signal
     */
    // h?u h?t ai cx dùng cái này
    SYNC=0;
    SPEN=1; // 1 = Serial port enabled (configures RC7/RX/DT and RC6/TX/CK pins as serial port pins)
  /* AsSyc Serial communication */     
    
   //Set 8-bit reception and transmission
    /*
     * TX9: 9-bit Transmit Enable bit
     * 1 = Selects 9-bit transmission/reception
     * 0 = Selects 8-bit transmission/reception
     */
    RX9=0;
    TX9=0;
    
    // Both sending and receiving
    TXEN=1;  // Enable transmit
    CREN=1; //Enable receive
    
    //Enable global and ph. interrupts//
    GIE = 1;
    PEIE= 1;
  
    //Enable interrupts for Tx. and Rx.//
    RCIE=1;
    TXIE=1;
}
    
void BT_load_char(char byte)
{
    while(TXIF==0);  // Doi den khi register transmitter trong   
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
    if(OERR == 1 ) // check for over run error 
    {
        CREN = 0;
        CREN = 1; //Reset CREN
    }
    
    // 
    if(RCIF==1) //if the user has sent a char return the char (ASCII value) // Doi den khi register transmitter trong   
    {
    while( RCIF == 0);     // Wait till the data is received 
    return RCREG;
    }
    else //if user has sent no message return 0
        return 0;
}
