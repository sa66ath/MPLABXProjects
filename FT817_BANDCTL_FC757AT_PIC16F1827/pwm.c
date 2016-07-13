#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>

#include "system.h"

#include "pwm.h"


void PwmInit(void)
{
    CCPTMRSbits.C1TSEL = 0b10;    // 10 = CCP2 is based off Timer 6 in PWM Mode
    
    T6CON = 0b0000<<_T6CON_T6OUTPS_POSITION |   // 0000 = 1:1 Postscaler
                 0<<_T6CON_TMR6ON_POSN |        // 0 = Timerx is off
              0b00<<_T6CON_T6CKPS_POSITION;     // 00 = Prescaler is 1
    PR6 = 0xff;
    TMR6ON = 1;


    // CCPR1L
    CCP1CON = 0b00<<_CCP1CON_P1M_POSN | // 00 = Single output; PxA modulated; PxB, PxC, PxD assigned as port pins
            0b11<<_CCP1CON_DC1B_POSITION |
            0b1100<<_CCP1CON_CCP1M_POSITION;    // 11xx = PWM mode
}

void PwmDuty(uint16_t val)
{
    CCPR1L = val>>(16-10+2);
    CCP1CON = (~_CCP1CON_DC1B_MASK & CCP1CON) |
            (_CCP1CON_DC1B_MASK & (val>>(16-10-_CCP1CON_DC1B_POSITION)));
}
 
