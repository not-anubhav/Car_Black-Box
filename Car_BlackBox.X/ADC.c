#include "black_box.h"

int digital_val;

void init_ADC()
{
    ADFM = 1; // Right Justified
    
    /* Conversion Time */
    ADCS2 = 0;
    ADCS1 = 1;
    ADCS0 = 0;
    
    /* Acquisition Time */
    ACQT2 = 1;
    ACQT1 = 0;
    ACQT0 = 0;
    
    /* Clear Garbage */
    ADRESH = 0;
    ADRESL = 0;
    
    /* Turn on ADC */
    GO = 0;
    ADON = 1;
}

int read_adc(char channel)
{
    
    ADCON0 = ADCON0 & 0xC3 | (channel << 2);
    
    GO = 1;
    while(GO);
    
    digital_val = ADRESL | (ADRESH << 8);
    
    return digital_val;
}
           
