/*
 * LED_mode, SEND_mode: done
 * Read and Send adc value to hc06: done
 * File:   main.c
 * Author: JBsnipper
 * Ref: Heart "Beat Monitoring using PIC Microcontroller and Pulse Sensor" on circuitdigest.com
 * Created on October 12, 2019, 4:23 PM
 */

#include "config.h"
#include <xc.h>
#include "adc.h"
#include "bluetooth.h"


void Pin_Init()
{
    TRISA = 0xFF;
    TRISB = 0;
    PORTB = 0xFF;
    __delay_ms(200);
    PORTB = 0;
    TRISD = 0;       
}

void main(void) {
    Pin_Init();
    Init_ADC();
    Initialize_Bluetooth();
        
    int blt_mess=0;
    BT_load_string("Bluetooth Initialized and Ready");
    broadcast_BT();
  
    char mess[20];
    float data = 0;
    unsigned int LED_mode = 1;
    unsigned int send_mode = 1;
    int time = 0;
    int i=0;
    while(1)
    {
        blt_mess = BT_get_char();
	if( blt_mess == '0' ) PORTB = 0;
        if( blt_mess == '1' ) PORTB = 0xFF;        
        if( blt_mess == '2' ) LED_mode= 0;
        if( blt_mess == '3' ) LED_mode = 1;
	if( blt_mess == '4' ) send_mode= 0;
        if( blt_mess == '5' ) send_mode = 1;
       if(ADCON0bits.GO_DONE == 0 ) 
        {
           time++;
            ADCON0bits.GO_DONE = 1;
            data = read_ADC();
            if(LED_mode == 1)
                if(data>62  && time > 😎 
            {
                time = 0;
                PORTB = 0xFF;
                __delay_ms(5);
                PORTB = 0;
            }
            
            if(send_mode == 1)
            {
            sprintf(mess, "%.2f",data);
            BT_load_string(mess);
            broadcast_BT();
            
            __delay_ms(50);
            }
          
        }
    };
    return;
}