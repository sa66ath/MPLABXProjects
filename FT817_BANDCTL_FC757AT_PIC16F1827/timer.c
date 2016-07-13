
#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>         /* For uint8_t definition */
#include "system.h"


#include "timer.h"



volatile unsigned long sys1ms;



void TimerInit(void)
{
    T2CON = 0b0000<<_T2CON_T2OUTPS_POSITION |   // 0000 = 1:1 Postscaler
                 0<<_T2CON_TMR2ON_POSN |        // 0 = Timerx is off
              0b01<<_T2CON_T2CKPS_POSITION;     // 01 = Prescaler is 4
    PR2 = (uint8_t)(FCY/1/4*0.001);     // 1ms

    TMR2ON = 1;
}

void TimerStart(void)
{
    TMR2IF = 0;
    TMR2IE = 1;
}

bool TimerSys1msElasped(unsigned long interval, unsigned long *saved)
{
        unsigned long now = TimerGetSys1ms();
        
        if(interval <= (now - *saved)) {
            for(; interval <= (now - *saved); *saved += interval) { ; }
            return true;
        }

        return false;
}

/******************************************************************************/
void TimerIncSys1ms(void)
{
    sys1ms++;
}

unsigned long TimerGetSys1ms(void)
{
    unsigned long now;

    TMR2IE = 0;
    now = sys1ms;
    TMR2IE = 1;

    return now;
}

