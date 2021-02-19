#include <xc.h>
#include "timers.h"
#include "RunMode.h"

/************************************************************************
 * FUNCTION to initialise 16 bit timer0:
*/
void Timer0_init(void)
{
    T0CON1bits.T0CS=0b010; // Fosc/4 (clock source)
    T0CON1bits.T0ASYNC=1; /* see datasheet errata - needed to ensure correct
                           * operation when Fosc/4 used as clock source*/
    T0CON1bits.T0CKPS = prescaler; //int prescaler defined in RunMode.h 
    T0CON0bits.T016BIT=1;	//16bit mode
	
    /*Alter the number of effective bits to reduce time overflow time:*/
    TMR0H = start_high; //int start_high defined in RunMode.h   
    TMR0L = start_low; //int start_low defined in RunMode.h 
    
    T0CON0bits.T0EN=1;	//start the timer
}

/************************************************************************
 * FUNCTION to return the 8 MSBits of the timer0 counter value:
*/
unsigned int get16bitTMR0val(void)
{
    unsigned int timer_counter = TMR0L; //read TMR0L first 
    timer_counter = TMR0H; //read TMR0H next (8 most significant counter bits) 
    return (timer_counter); //return the value
}

