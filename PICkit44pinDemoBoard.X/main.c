/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#if defined(__XC)
	#include <xc.h>        /* XC8 General Include File */
#elif defined(HI_TECH_C)
	#include <htc.h>       /* HiTech General Include File */
#elif defined(__18CXX)
	#include <p18cxxx.h>   /* C18 General Include File */
#endif

#if defined(__XC) || defined(HI_TECH_C)
	#include <stdint.h>        /* For uint8_t definition */
	#include <stdbool.h>       /* For true/false definition */

	#include <delays.h>
#endif

#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp */


/** D E F I N I T I O N S ****************************************************/
#define Switch_Pin      PORTBbits.RB0
#define DetectsInARow   5


/******************************************************************************/
/* User Global Variable Declaration                                           */
/******************************************************************************/

/* i.e. uint8_t <variable_name>; */

unsigned char LED_Display;  // 8-bit variable

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

void main(void)
{
    unsigned char Switch_Count = 0;

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize I/O and Peripherals for application */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    LED_Display = 1;	// initialize

    while(1)
    {

        LATD = ADC_Convert();
        /********
        LATD = LED_Display;     // output LED_Display value to PORTD LEDs

        LED_Display <<= 1;      // rotate display by 1

        if (LED_Display == 0)
            LED_Display = 1;    // rotated bit out, so set bit 0



        while (Switch_Pin != 1);// wait for switch to be released

        Switch_Count = 5;
        do
        { // monitor switch input for 5 lows in a row to debounce
            if (Switch_Pin == 0)
            { // pressed state detected
                Switch_Count++;
	    }
            else
            {
                Switch_Count = 0;
            }   
            Delay10TCYx(25);    // delay 250 cycles or 1ms.
        } while (Switch_Count < DetectsInARow);
         * *****/

    }

}

