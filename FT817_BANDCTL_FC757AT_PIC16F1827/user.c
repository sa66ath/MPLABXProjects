/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>         /* For uint8_t definition */
#include <stdbool.h>        /* For true/false definition */

#include "system.h"
#include "seg7_disp.h"
#include "timer.h"
#include "adc.h"
#include "pwm.h"
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
    ANSELA = 0x00;
    PORTA = 0b11111111;
    TRISA = 0b00100000;

    nWPUEN = 0; /* 0 = Weak pull-ups are enabled by individual WPUx latch values */

    // Pin8 RB2 -> AN10
    ANSELB = 0b00000100;
    PORTB = 0b11111111;

    WPUB = 0b11010011;
    TRISB = 0b11010111;

    /* Initialize peripherals */
    TimerInit();
    FVRInit();
    AdcInit();
    PwmInit();

    /* Enable interrupts */
    TimerStart();
    AdcStart();

    PEIE = 1;
    GIE = 1;
    
    PwmDuty(0x0000);
}



/******************************************************************************/
static unsigned long savedDot1ms;


static void DispDot(void)
{
    if(TimerSys1msElasped(100, &savedDot1ms)) {
        Seg7DotOn(!Seg7DotIsOn());
    }
}

static void DispReset(void)
{
    savedDot1ms = TimerGetSys1ms();
    
    Seg7DispClearNum();
    Seg7DotOn(false);
}

void AppMain() {
    

    FT817Band(AdcRead());


    if(RB1) {
        DispDot();
    } else {
        DispReset();
    }
}


