#ifndef RunMode_H
#define	RunMode_H

#include <xc.h>

/***********************************************************
 * USE - Keep one section uncommented to run device on the 
 *       relavant mode
 ************************************************************
 * VARIABLE DEFINITIONS and use locations:
 * prescaler - tmr0 prescaler (used in timers.c)
 * start_high - 8 MSBits of tmr0 start position 
 *               ^used in timers.c and interrupts.c)
 * start_low - 8 LSBits of tmr0 start position
 *               ^used in timers.c and interrupts.c)
 * secs_increment - direct prescaler for real-time secs 
 *                  ^used in interrupts.c
***********************************************************/ 


/***********************************************************
 * NORMAL MODE:
 * effect: seconds are incremented in real time
 */ 
#define prescaler (0b1000) //1:256
#define start_high (0b00001011) 
#define start_low (0b11011100)
#define secs_increment (1) 

/***********************************************************
 * TEST MODE 1:
 * effect: hours are incremented every 0.9999 seconds
 */ 
//#define prescaler (0b0000) //1:1
//#define start_high (0b11101110)
//#define start_low (0b10100100)
//#define secs_increment (1)

/***********************************************************
 * TEST MODE 2:
 * effect: days are incremented exactly every second
 */ 
//#define prescaler (0b0000) //1:1
//#define start_high (0b11101100)
//#define start_low (0b01111000)
//#define secs_increment (27)


#endif

