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
    TRISA = 0xFF;   // t?t c? c?ng A là input
    
    TRISB = 0x00;         // T?t c? c?ng B là d?ng output  
    
    PORTB = 0xFF;       // T?t c? chân ? c?ng B = 1
    
    // TRISB1 = 0  chân B1 là thu?c d?ng output
    // PORTB1= 1 thì là B1 nó ?ang mu?n output ngay bh = mu?n cho dòng ?i?n 25mA ra chân B1
    //PORTB1 = 0 B1 không mu?n output ngay bh
    
    __delay_ms(200);
    PORTB = 0;
    
    TRISD = 0;   // T?t c? chân D là output    
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
        blt_mess = BT_get_char();  // L?y trong không khí tín hi?u Bluetooth g?i v?
        // t? dt.   -> RX
        // Chuy?n data trong RX sang bi?t "blt_mess"
        if( blt_mess == '0' ) PORTB = 0;    // T?t ?èn
        if( blt_mess == '1' ) PORTB = 0xFF;        // Sáng ?èn
        
        if( blt_mess == '2' ) LED_mode= 0;      // B?t t?t ch? ?? "?èn sáng khi có nh?p tim"
        if( blt_mess == '3' ) LED_mode = 1;
        
	if( blt_mess == '4' ) send_mode= 0; //
        if( blt_mess == '5' ) send_mode = 1;
        
       if(ADCON0bits.GO_DONE == 0 ) 
        {
           time++;
            ADCON0bits.GO_DONE = 1;
            data = read_ADC(); // 0-> 100
            if(LED_mode == 1)
                if(data>62  && time > 8   ) 
            {
                time = 0;
                PORTB = 0xFF;
                __delay_ms(5);
                PORTB = 0;
            }
            
            if(send_mode == 1)
            {
                
                
            sprintf(mess, "%.2f",data);    
            // data là d?ng float -> string( m?ng các ph?n t? char ) l?u giá tr? c?a data
            // vào m?t bi?n dàng string tên là mess
            // float   data  12.34 -> mess  "12.64"
            
            BT_load_string(mess);   // N?p d? li?u string c?n g?i vào thanh ghi ?êm TX
            broadcast_BT();             // G?i t?t c? m?i th? ?ang ch?a trong thanh TX
            __delay_ms(50);
      
            
            }
          
        }
    };
    return;
}