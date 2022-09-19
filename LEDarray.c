#include <xc.h>
#include "LEDarray.h"

/**************************************************************************
 * FUNCTION used to initialise pins to drive the LEDarray:
 */
void LEDarray_init(void)
{
    /*set up TRIS registers for pins connected to LED array
     *(all relevant pins set to output)*/
    TRISGbits.TRISG0 = 0; 
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISFbits.TRISF6 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    
    /*set initial output (off) LAT values
     *(they may have random values when powered on)*/
    LATGbits.LATG0 = 0;
    LATGbits.LATG1 = 0;
    LATAbits.LATA2 = 0;
    LATFbits.LATF6 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;
    LATFbits.LATF0 = 0;
    LATBbits.LATB0 = 0;
    LATBbits.LATB1 = 0;
}

/**************************************************************************
 * FUNCTION used to display a number on the LED array in binary:
 */
void LEDarray_disp_bin(unsigned int number)
{
    if (number & 0b000000001){LATGbits.LATG0 = 1;} 
    else{LATGbits.LATG0 = 0;} //assign pin G0 to least significant bit
    
    if (number & 0b000000010){LATGbits.LATG1 = 1;} 
    else{LATGbits.LATG1 = 0;}
    
    if (number & 0b000000100){LATAbits.LATA2 = 1;} 
    else{LATAbits.LATA2 = 0;}
    
    if (number & 0b000001000){LATFbits.LATF6 = 1;} 
    else{LATFbits.LATF6 = 0;}
    
    if (number & 0b000010000){LATAbits.LATA4 = 1;} 
    else{LATAbits.LATA4 = 0;}
    
    if (number & 0b000100000){LATAbits.LATA5 = 1;} 
    else{LATAbits.LATA5 = 0;}
    
    if (number & 0b001000000){LATFbits.LATF0 = 1;} 
    else{LATFbits.LATF0 = 0;}
    
    if (number & 0b010000000){LATBbits.LATB0 = 1;} 
    else{LATBbits.LATB0 = 0;}
    
    if (number & 0b100000000){LATBbits.LATB1 = 1;} 
    else{LATBbits.LATB1 = 0;} //assign pin B1 to most significant bit
};
