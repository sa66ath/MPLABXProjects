/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "system.h"
#include "adc.h"
#include "ft817band.h"


#include "user.h"


/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */


    /* Setup analog functionality and port direction */
    nWPUEN = 0; /* 0 = Weak pull-ups are enabled by individual WPUx latch values */

    PORTA =
    LATA =   0b111011;
    ANSELA = 0b010000;    // Pin3. RA4 -> AN3
    WPUA =   0b101011;
    TRISA =  0b111011;

    PORTC = 
    LATC =   0b000000;
    ANSELC = 0b000000;
    TRISC =  0b000000;      // All OUTPUT

    /* Initialize peripherals */
    FVRInit();
    AdcInit();

    /* Enable interrupts */
    PEIE = 1;
    GIE = 1;
    
}



/******************************************************************************/
void AppMain() {
    FT817Band(AdcRead());
}


