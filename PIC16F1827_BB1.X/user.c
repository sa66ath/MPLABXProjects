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

//    WPUB = 0b11011011;
//    TRISB = 0b11011111;
    WPUB = 0b11010011;
    TRISB = 0b11010111;

    /* Initialize peripherals */
    TimerInit();
    AdcInit();
    PwmInit();

    /* Enable interrupts */
    TimerStart();
    AdcStart();

    PEIE = 1;
    GIE = 1;
}



/******************************************************************************/
static unsigned long savedHex1ms;
static unsigned long savedDot1ms;
static int dispHex = 0;

static void DispHex(void)
{
    if(TimerSys1msElasped(1000, &savedHex1ms)) {
        Seg7DispHex(dispHex);
        dispHex++;
        dispHex = (0x0f < dispHex)? 0:dispHex;
    }
}

static void DispDot(void)
{
    if(TimerSys1msElasped(100, &savedDot1ms)) {
        Seg7DotOn(!Seg7DotIsOn());
    }
}

static bool DispReset(bool reset)
{
    if(reset) {
        savedHex1ms = savedDot1ms = TimerGetSys1ms();
    
        Seg7DotOn(false);
        Seg7DispHex(dispHex = 0);
        dispHex++;
    }

    return reset;
}

void AppMain() {
    uint16_t adcResult; 
    
    adcResult = AdcRead();

    PwmDuty(adcResult);
/*++++++++++
    static char hex;

    adcResult = AdcRead();
    
    if(hex != (adcResult>>(16-4))) {
        Seg7DispHex(hex = (adcResult>>(16-4)));
    }
    DispDot();
++++++++++++++*/

    if(RB1) {
        DispHex();
        DispDot();
    } else {
        DispReset(true);
    }
}


