/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */

#include "adc.h"

#include "user.h"
/******************************************************************************/
/* Interrupt Routines                                                         */
/******************************************************************************/

/* Baseline devices don't have interrupts. Note that some PIC16's 
 * are baseline devices.  Unfortunately the baseline detection macro is 
 * _PIC12 */
#ifndef _PIC12

// void interrupt isr(void)
void __interrupt() isr(void)
{
    /* This code stub shows general interrupt handling.  Note that these
    conditional statements are not handled within 3 seperate if blocks.
    Do not use a seperate if block for each interrupt flag to avoid run
    time errors. */

    if(ADIF) {
        ADIF = 0;
        AdcIsr();
    }

#if 0
    
    /* TODO Add interrupt routine code here. */

    /* Determine which flag generated the interrupt */
    if(<Interrupt Flag 1>)
    {
        <Interrupt Flag 1=0>; /* Clear Interrupt Flag 1 */
    }
    else if (<Interrupt Flag 2>)
    {
        <Interrupt Flag 2=0>; /* Clear Interrupt Flag 2 */
    }
    else
    {
        /* Unhandled interrupts */
    }

#endif

}
#endif


