#include <xc.h>
#include "datetime.h" //import to recognise seconds_counter variable
#include "timers.h" //import to recognise run mode variables

bool sun; /*define global variable sunlight to be used across files (see datetime.h)*/
unsigned int seconds_check; /*define global variable checking seconds to be
                                 used across files (see datetime.h)*/

//define a counter with time period of 1s that increments infinitely:
unsigned int seconds_counter;  /*define global variable seconds to be
                                 used across files (see datetime.h)*/

/***************************************************************************
 * FUNCTION to calculate the current time and return any specified subunit 
 *         (uncommented subunit at the end).
 * INPUT : (start minute, start hour, start weekday, start day, start month, 
 *          start year, start season).
 * OUTPUT: returns any subunit of current time and autumatically updates 
 *         the start time.
 */
unsigned int time_now(unsigned int *seconds, unsigned int *minutes, unsigned int *hours, 
                      unsigned int *weekdays,unsigned int *days, 
                      unsigned int *months, unsigned int *years,
                      unsigned int *season)
{
    
    bool leap = !(*years % 4);  //variable leap is 1 on leap years and 0 others
    
    //int array month_days that contains no of days in all months:
    unsigned int month_days[] = {31, 28 + leap, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};
    
    unsigned int cur_month = month_days[*months]; /* variable which finds number
                                                  of days in the current month*/
    
    //if current date & time is 1am on the last sunday of march...
    if ((*months == 2) && (*days > 23) && (*weekdays == 6) && (*hours == 1))
    {
        *season = 1; //set season to be summer
        *hours += 1; //move forward an hour
    }
    
    //if current date & time is 2am on the last sunday of october...
    if ((*months == 9) && (*days > 23) && (*weekdays == 6) && (*hours == 2)
         && (*season == 1))
    {
        *season = 0; //set season to be winter
        *hours -= 1; //move back an hour
    }
    
    *minutes += *seconds / 60;  //increment minute every 60 seconds
    *seconds %= 60; //cap second at 60 and reset
    *hours += *minutes / 60;  //increment hour every 60 minutes
    *minutes %= 60; //cap minute at 60 and reset
    *days += *hours / 24; //increment day every 24 hours
    *weekdays += *hours / 24; //increment weekday every 24 hours
    *hours %= 24; //cap hour at 24 and reset
    *months += *days / cur_month; /*increment month every 28 or 29 or 30 or 31
                                    days depending on current month*/
    *days %= cur_month; //cap day at (28 or 29 or 30 or 31) and reset
    *weekdays %= 7; //cap day at 7 and reset
    *years += *months / 12; //increment year every 12 months
    *months %= 12; //cap month at 12 and reset
    
    //output (select one):
    
//    return (*seconds); //return current second
//    return (*minutes); //return current minute
    return (*hours); //return current hour
//    return (*days); //return current day
//    return (*months); //return current month
//    return (*years); //return current year
}


/***************************************************************************
 * FUNCTION to return the current time as a string.
 * INPUT : (display string, start minute, start hour, start weekday, start day, start month, 
 *          start year, start season).
 * OUTPUT: returns current time in the format of hh:mm:ss.
 */
void time_now_display(char *timebuf, unsigned int *seconds, unsigned int *minutes, unsigned int *hours, 
                      unsigned int *weekdays,unsigned int *days, 
                      unsigned int *months, unsigned int *years,
                      unsigned int *season)
{
    
    bool leap = !(*years % 4);  //variable leap is 1 on leap years and 0 others
    
    //int array month_days that contains no of days in all months:
    unsigned int month_days[] = {31, 28 + leap, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};
    
    unsigned int cur_month = month_days[*months]; /* variable which finds number
                                                  of days in the current month*/
    
    //if current date & time is 1am on the last sunday of march...
    if ((*months == 2) && (*days > 23) && (*weekdays == 6) && (*hours == 1))
    {
        *season = 1; //set season to be summer
        *hours += 1; //move forward an hour
    }
    
    //if current date & time is 2am on the last sunday of october...
    if ((*months == 9) && (*days > 23) && (*weekdays == 6) && (*hours == 2)
         && (*season == 1))
    {
        *season = 0; //set season to be winter
        *hours -= 1; //move back an hour
    }
    
    *minutes += *seconds / 60;  //increment minute every 60 seconds
    *seconds %= 60; //cap second at 60 and reset
    *hours += *minutes / 60;  //increment hour every 60 minutes
    *minutes %= 60; //cap minute at 60 and reset
    *days += *hours / 24; //increment day every 24 hours
    *weekdays += *hours / 24; //increment weekday every 24 hours
    *hours %= 24; //cap hour at 24 and reset
    *months += *days / cur_month; /*increment month every 28 or 29 or 30 or 31
                                    days depending on current month*/
    *days %= cur_month; //cap day at (28 or 29 or 30 or 31) and reset
    *weekdays %= 7; //cap day at 7 and reset
    *years += *months / 12; //increment year every 12 months
    *months %= 12; //cap month at 12 and reset
    
    //output:
    
    sprintf(timebuf, "    %02d:%02d:%02d", *hours, *minutes, *seconds); /*stores ADC value to 2dp
                                                   *as a string in buf*/
}

/***************************************************************************
 * FUNCTION to return the current date as a string.
 * INPUT : (display string, start minute, start hour, start weekday, start day, start month, 
 *          start year, start season).
 * OUTPUT: returns current time in the format of dd mm yyyy.
 */
void date_now_display(char *datebuf, unsigned int *seconds, unsigned int *minutes, unsigned int *hours, 
                      unsigned int *weekdays,unsigned int *days, 
                      unsigned int *months, unsigned int *years,
                      unsigned int *season)
{
    
    bool leap = !(*years % 4);  //variable leap is 1 on leap years and 0 others
    
    //int array month_days that contains no of days in all months:
    unsigned int month_days[] = {31, 28 + leap, 31, 30, 31, 30,
                                 31, 31, 30, 31, 30, 31};
    
    unsigned int cur_month = month_days[*months]; /* variable which finds number
                                                  of days in the current month*/
    
    //if current date & time is 1am on the last sunday of march...
    if ((*months == 2) && (*days > 23) && (*weekdays == 6) && (*hours == 1))
    {
        *season = 1; //set season to be summer
        *hours += 1; //move forward an hour
    }
    
    //if current date & time is 2am on the last sunday of october...
    if ((*months == 9) && (*days > 23) && (*weekdays == 6) && (*hours == 2)
         && (*season == 1))
    {
        *season = 0; //set season to be winter
        *hours -= 1; //move back an hour
    }
    
    *minutes += *seconds / 60;  //increment minute every 60 seconds
    *seconds %= 60; //cap second at 60 and reset
    *hours += *minutes / 60;  //increment hour every 60 minutes
    *minutes %= 60; //cap minute at 60 and reset
    *days += *hours / 24; //increment day every 24 hours
    *weekdays += *hours / 24; //increment weekday every 24 hours
    *hours %= 24; //cap hour at 24 and reset
    *months += *days / cur_month; /*increment month every 28 or 29 or 30 or 31
                                    days depending on current month*/
    *days %= cur_month; //cap day at (28 or 29 or 30 or 31) and reset
    *weekdays %= 7; //cap day at 7 and reset
    *years += *months / 12; //increment year every 12 months
    *months %= 12; //cap month at 12 and reset
    
    char daylist[7][10] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    //output:
    
    sprintf(datebuf, " %s %02d/%02d/%04d", daylist[*weekdays], *days + 1, *months + 1, *years); /*stores ADC value to 2dp
                                                   *as a string in buf*/
}