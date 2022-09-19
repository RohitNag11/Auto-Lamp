#include <xc.h>
#include "interrupts.h"
//#include "timers.h"
#include "datetime.h"
#include "RunMode.h"
#include <stdio.h>



/************************************************************************
 * FUNCTION to turn on interrupts and set priorities
 */
void Interrupts_init(void)
{
    INTCONbits.PEIE=1; //turn on peripheral interrupts
    INTCONbits.IPEN=1; //enable interrupt priority feature
    
	PIE2bits.C1IE = 1; //enable bit 2 peripheral interrupts
    PIE0bits.TMR0IE = 1; //enable bit timer0 interrupts
    
    IPR2bits.C1IP = 0; //set priority of peripheral interrupt to low
    IPR0bits.TMR0IP = 1; //set priority of timer0 interrupt to high
    
    INTCONbits.GIE=1; 	/*turn on interrupts globally 
                         *(when this is off, all interrupts are deactivated)*/
}

/************************************************************************
 * Low priority interrupt service routine
 * PURPOSE: switches LED 2 output state if LDR receives low light
*/
void __interrupt(low_priority) LdrISR()
{
	if(PIR2bits.C1IF)  //check the bit 2 peripheral flag
    {
        printf("hello");
        PIR2bits.C1IF = 0; //clear the interrupt flag
        sun = !sun;
        if (sun) {
            seconds_check = 0;
        }
	}
}

/************************************************************************
 * High priority interrupt service routine
 * PURPOSE: increments seconds_counter every overflow
 *          and maintains timer0 start position
*/
void __interrupt(high_priority) TimerISR()
{
    if (PIR0bits.TMR0IF) //check the TMR0 interrupt flag is 1
                         //true when when timer0 overflows
    {
        PIR0bits.TMR0IF = 0; //clear the timer0 interrupt flag
        seconds_counter += secs_increment; //seconds prescaler, see RunMode.h
        //set correct counter start position after every overflow:
        TMR0H = start_high;   
        TMR0L = start_low;
        if (sun){
            seconds_check += secs_increment;
        }
    }
}