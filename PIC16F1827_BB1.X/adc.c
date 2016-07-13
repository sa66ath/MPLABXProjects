#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */

#include "system.h"
#include "adc.h"


uint16_t adData;

static void AdcTimerInit(void)
{
    T4CON = 0b0011<<_T4CON_T4OUTPS_POSITION |   // 0011 = 1:4 Postscaler
                 0<<_T4CON_TMR4ON_POSN |        // 0 = Timerx is off
              0b10<<_T4CON_T4CKPS_POSITION;     // Prescaler is 16
    PR4 = (uint8_t)(FCY/4/16*0.01);     // FCY/Postscaler/Prescaler*sec

    TMR4IF = 0;
    TMR4IE = 0;
}


void AdcInit(void)
{
    ADCON0 = 10<<_ADCON0_CHS_POSITION |
             1<<_ADCON0_ADON_POSITION;      // 1 = ADC is enabled

    ADCON1 = 0<<_ADCON1_ADFM_POSITION |     // 0 = Left justified. Six Least Significant bits of ADRESL are set to ?0? when the conversion result is loaded.
            0b001<<_ADCON1_ADCS_POSITION |  // 001 = FOSC/8
            0<<_ADCON1_ADNREF_POSITION |    // 0 = VREF- is connected to AVSS
            0b00<<_ADCON1_ADPREF_POSITION;  // 00 = VREF+ is connected to AVDD

    AdcTimerInit();
    
    ADIE = 1;  
    TMR4IE = 1;
}

void AdcStart(void)
{
    TMR4ON = 1;
}

uint16_t AdcRead(void)
{
    uint16_t read;

    ADIE = 0;
    read = adData;
    ADIE = 1;

    return read;
}

void AdcIsr(void)
{
    adData = ADRESH<<8 | ADRESL;
}
