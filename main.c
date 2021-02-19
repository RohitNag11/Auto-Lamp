// CONFIG1L
#pragma config FEXTOSC = HS         /* External Oscillator mode Selection bits 
                                     * (HS (crystal oscillator) above 8 MHz; 
                                     * PFM set to high power)*/

#pragma config RSTOSC = EXTOSC_4PLL /* Power-up default value for COSC bits 
                                     * (EXTOSC with 4x PLL, with EXTOSC 
                                     * operating per FEXTOSC bits)*/

// CONFIG3L
#pragma config WDTE = OFF   //WDT enabled regardless of sleep

//Import header files:
#include <xc.h>
#include "LEDarray.h"
#include "interrupts.h"
#include "comparator.h"
#include "timers.h"
#include "datetime.h"
#include "RunMode.h"
#include "LCD.h"

#define _XTAL_FREQ 64000000     //oscillator frequency is 64,000,000Hz  


void main(void) {
    
    LCD_Init();             //Initialise the LCD screen
    Timer0_init();          //initialise and start timer
    LEDarray_init();        //initialise LED array
    Interrupts_init();      //enable interrupts
    Comp1_init();           //Initialise comparator
    
    TRISFbits.TRISF7=1;     //Set pin f7 to input
    ANSELFbits.ANSELF7=1;   //Set pin f7 to analogue input
    
    //Configure LED1 (virtual sun):
    TRISDbits.TRISD7 = 0;   //set LED1 to output
    LATDbits.LATD7 = 1;     //set initial LED1 state to on
    
    //Configure LED2 (lamp):
    TRISHbits.TRISH3 = 0;   //set LED2 to output
    LATHbits.LATH3 = 1;     //set initial LED2 state to on
    

    /*************************************************************************
     * INPUT Variable to decide if device start is during sunlight or night
     * NOTE: set this to be opposite of the correct initial state
     * EXAMPLE: if initialised during daytime, set to 0.
     */
    sun = 0;
    
    bool prev_sun = sun;    /*variable defining the old copy of sun*/
    
    /*************************************************************************
     *INPUT start time for when device is turned on:
     * start_time[] format: [sec, min, hr, weekday, day, month, yr, season]
     * 
     * sec format: 0,1,2,...,58,59
     * min format: 0,1,2,...,58,59
     * hour format: 0,1,2,...,22,23 
     * weekday format: 0,1,2,...,5,6 (mon, tues, wed,..., sat, sun)
     * day format: 0,1,2,...,27 or 28 or 29 or 30 (depending on month)
     * month format: 0,1,2,...,10,11 (jan, feb, mar,..., nov, dec)
     * yr format: 2000,2001,...infinity
     * season format: 0 (winter), 1 (summer). -see note below
     * note: Summer is between the last sundays of March and October
     * 
     *EXAMPLE: {0, 50, 22, 5, 29, 9, 2021, 1}
     *        = 22:50:00, Saturday 30th Oct 2021, Summer 
     */
    unsigned int start_time[] = {0, 0, 0, 0, 0, 0, 2021, 0};
    
    seconds_counter = start_time[0];    /*set seconds timer to start at user-
                                         * inputted seconds start time*/
    unsigned int prev_sec = 0;  /*variable defining the old copy of
                                 * seconds_counter*/
    
    char timebuf[40];//define a 40 characters length string to display on LCD
    char datebuf[40];//define a 40 characters length string to display on LCD
    while (1)
    {
        if (seconds_counter != prev_sec) //if seconds_counter changes...
        {
            //find the current hour in real-time:
            unsigned int hour_now = time_now(timebuf, datebuf, 
                                             &seconds_counter, &start_time[1], 
                                             &start_time[2], &start_time[3], 
                                             &start_time[4], &start_time[5], 
                                             &start_time[6], &start_time[7]);
            
            //recalibrate time at sunset:
            if ((sun != prev_sun) && (!sun))
            {
                start_time[1] = 0; //elapsed minutes from noon = 0
                start_time[2] = 12; //elapsed hours from noon = 12
                seconds_counter = seconds_check/2; /*time in seconds
                                                    *elapsed past noon*/
            }
            
            //Turn on LED1 (virual sun) during daytime and off at night:
            LATDbits.LATD7 = sun;
            
            //force LE2 (lamp) be turned off between 1am and 5am:
            LATHbits.LATH3 = !(((hour_now > 0) && (hour_now < 6)) || sun);
            
            LEDarray_disp_bin(hour_now); /*display the current hour in binary 
                                          *on the LED array */
            prev_sec = seconds_counter; //copy seconds_counter before it changes
            prev_sun = sun; //copy sun state before it changes
            
            //Display date and time on the LCD screen:
            LCD_setline(1); //write to first line
            LCD_sendstring(timebuf); //display time
            
            LCD_setline(2); //write to second line
            LCD_sendstring(datebuf); //display date
            
            LCD_sendbyte(0b00000010, 0); /*write data from the start position
                                          * of the LCD every cycle*/
        } 
    }
}
