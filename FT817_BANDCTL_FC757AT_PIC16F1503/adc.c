#include <xc.h>         /* XC8 General Include File */

#include <stdint.h>        /* For uint8_t definition */

#include "system.h"
#include "adc.h"

/*----------------------------------------------------------------------*/
#define ADC_CH  0b00011     // 00011 = AN3
#define FVR_CH  0b11111     // 11111 =FVR (Fixed Voltage Reference) Buffer 1 Output

uint16_t adcData;
uint16_t fvrData;


/*----------------------------------------------------------------------*/
void FVRInit(void)
{
    FVRCON = 0b11<<_FVRCON_ADFVR_POSITION |     // 11 = ADC Fixed Voltage Reference Peripheral output is 4x (4.096V)
           0b00<<_FVRCON_CDAFVR_POSITION |      // 00 = Comparator and DAC Fixed Voltage Reference Peripheral output is off. 
           0<<_FVRCON_TSRNG_POSITION |          // 0 = VOUT = VDD - 2VT (Low Range). Default.
           0<<_FVRCON_TSEN_POSITION |           // 0 = Temperature Indicator is disabled. Default.
           1<<_FVRCON_FVREN_POSITION;           // 1 = Fixed Voltage Reference is enabled

    //  while(!FVRRDY)   { ; }               // 1 = Fixed Voltage Reference output is ready for use
    //                                          Note 1: FVRRDY is always ‘1’ for the PIC16F1503 devices.
}

static void AdcTimerInit(void)
{
    T2CON = 0b0000<<_T2CON_T2OUTPS_POSITION |  // 0000 = 1:1 Postscaler
                 0<<_T2CON_TMR2ON_POSN |        // 0 = Timerx is off
              0b10<<_T2CON_T2CKPS_POSITION;     // 10 = Prescaler is 16
    PR2 = (uint8_t)(FCY/1/16*0.005);     // FCY/Postscaler/Prescaler*sec

}


void AdcInit(void)
{
    ADCON0 = ADC_CH<<_ADCON0_CHS_POSITION |
             1<<_ADCON0_ADON_POSITION;      // 1 = ADC is enabled

    ADCON1 = 0<<_ADCON1_ADFM_POSITION |     // 0 = Left justified. Six Least Significant bits of ADRESL are set to ?0? when the conversion result is loaded.
            0b100<<_ADCON1_ADCS_POSITION |  // 100 = FOSC/4
            0b00<<_ADCON1_ADPREF_POSITION;  // 00 = VREF+ is connected to AVDD

    ADCON2 = 0b0101<<_ADCON2_TRIGSEL_POSITION;    // 0101 = TMR2 Match to PR2

    AdcTimerInit();
    
    ADIF = 0;
    ADIE = 1;  
    
    TMR2ON = 1;
}

uint16_t dummyAD;

uint16_t AdcRead(void)
{
    uint32_t tmp;
    uint16_t adc, fvr;

    ADIE = 0;
    adc = adcData;
    fvr = fvrData;
    ADIE = 1;

    tmp = (uint32_t)adc<<16; 
    tmp /= (fvr)? fvr:0x0001;

    tmp = (UINT16_MAX < tmp)? UINT16_MAX:tmp;

    return tmp;
}

void AdcIsr(void)
{
    uint16_t data = ADRESH<<8 | ADRESL;

    LATC4 = 1;  //+++++++++++

    switch(ADCON0bits.CHS) {
        case FVR_CH:
            fvrData = data;
            ADCON0bits.CHS = ADC_CH;
            break;
        case ADC_CH:
        default:
            adcData = data;
            ADCON0bits.CHS = FVR_CH;
            break;
    }
    
    LATC4 = 0;  //+++++++++++
}
