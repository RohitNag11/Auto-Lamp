#ifndef _datetime_H
#define	_datetime_H

#include <xc.h>
#include<stdbool.h>   //import boolean function
#include <stdio.h>


#define _XTAL_FREQ 64000000

extern bool (sun); /*GLOBAL VARIABLE
                    *communicate with other files to
                    * locate sun variable*/

extern unsigned int (seconds_check);

extern unsigned int (seconds_counter); /*GLOBAL VARIABLE
                                        *communicate with other files to
                                         locate seconds variable*/

unsigned int time_now(char *timebuf, char *datebuf, unsigned int *seconds, unsigned int *minutes, unsigned int *hours, 
                      unsigned int *weekdays,unsigned int *days, 
                      unsigned int *months, unsigned int *years,
                      unsigned int *season);
#endif