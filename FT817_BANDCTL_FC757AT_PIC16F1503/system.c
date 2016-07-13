/******************************************************************************/
/*Files to Include                                                            */
/******************************************************************************/


#include <xc.h>         /* XC8 General Include File */


// #include <stdint.h>        /* For uint8_t definition */
// #include <stdbool.h>       /* For true/false definition */

#include "system.h"

/* Refer to the device datasheet for information about available
oscillator configurations. */
void ConfigureOscillator(void)
{
    /* TODO Add clock switching code if appropriate.  */

    /* Typical actions in this function are to tweak the oscillator tuning
    register, select new clock sources, and to wait until new clock sources
    are stable before resuming execution of the main project. */

    OSCCON = 0b1011<<_OSCCON_IRCF_POSITION |  // 1011 = 1MHz HF
            0b00<<_OSCCON_SCS_POSITION;
    
}
