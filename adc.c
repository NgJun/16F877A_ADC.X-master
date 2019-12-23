#include "adc.h"



void Delay_adc(int cnt)
{
    while(cnt--);
}
void Init_ADC()
{ 
    // Ch?n t?n s? chuy?n ??i ADC
    //  Fosc/64
    ADCON0bits.ADCS0 = 0;
    ADCON0bits.ADCS1 = 1;
    ADCON1bits.ADCS2 = 1;
    
    // Ch?n k�nh giao ti?p : AN0
    ADCON0bits.CHS0=0;
    ADCON0bits.CHS1=0;
    ADCON0bits.CHS2=0;
    
    
    ADCON1bits.ADFM = 1; // c?n l? ph?i
    
    // T?t c? ch�n AN l� input Analog
    ADCON1bits.PCFG0 = 0;
    ADCON1bits.PCFG1 = 0;
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG3 = 0;
    
    ADCON0bits.GO_DONE = 1; // Tr?ng th�i 0 l� busy, 1 l� r?nh v� s? l�m bh
    ADCON0bits.ADON = 1;        // b?t c�i ADC l�n
}

float read_ADC()
{
    float data = 0;
    data =  ((ADRESH << 8) + ADRESL);   // 
    data = (data/1023.0 * 100);                 // 2^10 -1
    return data;
}
