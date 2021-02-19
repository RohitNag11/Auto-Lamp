#include <xc.h>
#include "LCD.h"
#include <stdio.h>

/******************************************************************************
 * FUNCTION to toggle LCD enable bit on then off
 * when this function is called the LCD screen reads the data lines
 */
void LCD_E_TOG(void) {
    LCD_E = 1; //turn the LCD enable bit on
    __delay_us(5); //wait a short delay
    LCD_E = 0; //turn the LCD enable bit off again
}

/******************************************************************************
 * FUNCTION to set the 4-bit data line levels for the LCD
 */
void LCD_sendnibble(unsigned char number) {
 
    if (number & 0b1000) {
        LCD_DB7 = 1;
    } else {
        LCD_DB7 = 0;
    }
    
    if (number & 0b0100) {
        LCD_DB6 = 1;
    } else {
        LCD_DB6 = 0;
    }
    
    if (number & 0b0010) {
        LCD_DB5 = 1;
    } else {
        LCD_DB5 = 0;
    }
    
    if (number & 0b0001) {
        LCD_DB4 = 1;
    } else {
        LCD_DB4 = 0;
    } 

    LCD_E_TOG(); /*toggle the enable bit to instruct the LCD to read the 
                     * data lines*/
    __delay_us(5); //Delay 5uS
}

/******************************************************************************
 * FUNCTION to send full 8-bit commands/data over the 4-bit interface
 * high nibble (4 most significant bits) are sent first, then low nibble sent
 */
void LCD_sendbyte(unsigned char Byte, char type) {
    LCD_RS = type; /* set RS pin whether it is a Command (0) 
                     * or Data/Char (1) using type argument*/
    LCD_sendnibble(Byte >> 4); /* send high bits of Byte using
                                             *  LCDout function*/
    LCD_sendnibble(Byte & 0b00001111); /* send low bits of Byte
                                        *  using LCDout function*/
    __delay_us(50); //delay 50uS (minimum for command to execute)
}

/******************************************************************************
 * FUNCTION to initialise the LCD after power on
 */
void LCD_Init(void) {
    //Define LCD Pins as Outputs:
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB2 = 0;
    TRISEbits.TRISE3 = 0;
    TRISEbits.TRISE1 = 0;
 
    /*set all pins low
     *(might be random values on start up, fixes lots of issues)*/

    LCD_RS = 0;
    LCD_E = 0;
    LCD_DB4 = 0;
    LCD_DB5 = 0;
    LCD_DB6 = 0;
    LCD_DB7 = 0;

    //Initialisation sequence code:
    //1. Wait for more than 40 ms after VDD rises to 4.5 V
    __delay_ms(50);
 
    //2. Function set 1
    LCD_sendnibble(0b0011);
    
    //3. Wait for more than 39us
    __delay_us(40);

    //4. Function set 2
    LCD_sendbyte(0b00101000, 0);
 
    //5. Wait for more than 39 ?s
    __delay_us(40);

    //6. Function set 3
    LCD_sendbyte(0b00101000, 0);
    
    //7. Wait for more than 37us
    __delay_us(40);
    
    //8. Display ON/OFF control
    LCD_sendbyte(0b00001111, 0);
    
    //7. Wait for more than 37 ?s
    __delay_us(40);
    
    //8. Display Clear
    LCD_sendbyte(0b00000001, 0);
    
    //9. Wait for more than 1.53ms
    __delay_us(1530);
    
    //10. Entry Mode Set
    LCD_sendbyte(0b00000101, 0);

    //Turn LCD display back on:
    LCD_sendbyte(0b00001100, 0);
 }

/******************************************************************************
 * FUNCTION to set the cursor to beginning of line 1 or 2
 */
void LCD_setline(char line) {
    if (line == 1) {
        LCD_sendbyte(0x80, 0); //Send 0x80 to set line to 1 (0x00 ddram address)
    }
    if (line == 2) {
        LCD_sendbyte(0xC0, 0); //Send 0xC0 to set line to 2 (0x40 ddram address)
    }
}

/******************************************************************************
 * FUNCTION to send string to LCD screen
 */
void LCD_sendstring(char *string) {
    while (*string != 0) //while character in location
{
        LCD_sendbyte(*string++, 1); //send single character LCD
	}

}

/******************************************************************************
 * FUNCTION to scroll to LCD screen
 * (shift display to the right)
 */
void LCD_scroll(void) {
    //Shift enough times to fit 40 characters on 16 bit display (24 shifts):
    for (char i = 24; i > 0; i--) {
        __delay_ms(300); //Have a small delay before executing scroll
        LCD_sendbyte(0b00011000, 0); //shift display to the right
}
}

/******************************************************************************
 * FUNCTION takes a ADC value and works out the voltage to 2 dp
 * the result is stored in buf as ascii text ready for display on LCD
 * Note result is stored in a buffer using pointers, it is not sent to the LCD
 */
void Time2String(char *buf, unsigned int sec) {
    //code to calculate the integer and fractions part of a ADC value
    // and format as a string using sprintf (see GitHub readme)
//    unsigned int int_part = sec/77; /*Calculate integer part:
//                                         * Scale ADC result so it is out of 
//                                         * 3.3V and rounded down to the
//                                         * nearest integer*/
//    unsigned int frac_part = (ADC_val*100)/77 - int_part*100; /*Calculate
//                                                            *fractional part*/
//    sprintf(buf, "%d.%02d", int_part, frac_part); /*stores ADC value to 2dp
//                                                   *as a string in buf*/
    sprintf(buf, "%02d", sec); /*stores ADC value to 2dp
                                                   *as a string in buf*/
}

//void LCD_scroll7(void) { //scroll to shift display to right 7 steps with delay
//    //Shift enough times to fit 40 characters on 16 bit display (24 shifts):
//    for (char i = 0; i < 7; i++) {
//        LCD_sendbyte(0b00011100, 0); //shift display to the right
//        __delay_ms(100); //Have a small delay before executing scroll
//}
//}
//
//void LCD_scroll7c(void) { //scroll to shift display to right 7 steps without delay
//    //Shift enough times to fit 40 characters on 16 bit display (24 shifts):
//    for (char i = 0; i < 7; i++) {
//        LCD_sendbyte(0b00011100, 0); //shift display to the right
//        
//}
//}
