#include <xc.h>

#include <stdint.h>

#include "system.h"
#include "seg7_disp.h"

#include "ft817band.h"

                    // Real     Ideal
#define	BAND00_VOLT	0.0     // 0.00 // THRU
#define	BAND01_VOLT	0.31    // 0.33	// 1.9M
#define	BAND02_VOLT	0.68    // 0.67	// 3.5M
#define	BAND03_VOLT	0.98    // 1.0	// 7M
#define	BAND04_VOLT	1.30    // 1.33	// 10M
#define	BAND05_VOLT	1.60    // 1.67	// 14M
#define	BAND06_VOLT	1.98    // 2.0	// 18M
#define	BAND07_VOLT	2.30    // 2.33	// 21M
#define	BAND08_VOLT	2.51    // 2.67	// 24.5M
#define	BAND09_VOLT	2.85    // 3.0	// 28M
#define	BAND10_VOLT	3.21    // 3.33	// 50M
#define	BAND11_VOLT	3.54    // 3.67	// 144M
#define	BAND12_VOLT	3.85    // 4.0	// 430M

#define	THRE_HYSTERESIS	0.2/2   // persent

#define	REF_VOLT	(4*1.024)	    /* Fixed Voltage Reference (FVR) */
#define	ADC_MAX		UINT16_MAX



static const uint16_t upThre[] = {
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND01_VOLT + (0.5 - THRE_HYSTERESIS)*BAND00_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND02_VOLT + (0.5 - THRE_HYSTERESIS)*BAND01_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND03_VOLT + (0.5 - THRE_HYSTERESIS)*BAND02_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND04_VOLT + (0.5 - THRE_HYSTERESIS)*BAND03_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND05_VOLT + (0.5 - THRE_HYSTERESIS)*BAND04_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND06_VOLT + (0.5 - THRE_HYSTERESIS)*BAND05_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND07_VOLT + (0.5 - THRE_HYSTERESIS)*BAND06_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND08_VOLT + (0.5 - THRE_HYSTERESIS)*BAND07_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND09_VOLT + (0.5 - THRE_HYSTERESIS)*BAND08_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND10_VOLT + (0.5 - THRE_HYSTERESIS)*BAND09_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND11_VOLT + (0.5 - THRE_HYSTERESIS)*BAND10_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 + THRE_HYSTERESIS)*BAND12_VOLT + (0.5 - THRE_HYSTERESIS)*BAND11_VOLT) /REF_VOLT *ADC_MAX),
    ADC_MAX
};

static const uint16_t downThre[] = {
    0,
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND01_VOLT + (0.5 + THRE_HYSTERESIS)*BAND00_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND02_VOLT + (0.5 + THRE_HYSTERESIS)*BAND01_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND03_VOLT + (0.5 + THRE_HYSTERESIS)*BAND02_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND04_VOLT + (0.5 + THRE_HYSTERESIS)*BAND03_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND05_VOLT + (0.5 + THRE_HYSTERESIS)*BAND04_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND06_VOLT + (0.5 + THRE_HYSTERESIS)*BAND05_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND07_VOLT + (0.5 + THRE_HYSTERESIS)*BAND06_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND08_VOLT + (0.5 + THRE_HYSTERESIS)*BAND07_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND09_VOLT + (0.5 + THRE_HYSTERESIS)*BAND08_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND10_VOLT + (0.5 + THRE_HYSTERESIS)*BAND09_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND11_VOLT + (0.5 + THRE_HYSTERESIS)*BAND10_VOLT) /REF_VOLT *ADC_MAX),
    (uint16_t)(((0.5 - THRE_HYSTERESIS)*BAND12_VOLT + (0.5 + THRE_HYSTERESIS)*BAND11_VOLT) /REF_VOLT *ADC_MAX)
};



size_t GetIndexWithHysteresis(size_t index, uint16_t val, const uint16_t* upTbl, const uint16_t* downTbl, size_t tblSize)
{
    /****   index = (0 <= index)?	index:0;    ****/
    index = (index < tblSize)?	index:tblSize - 1;

    for( ; upTbl[index] < val; index++) { ; }
    for( ; val < downTbl[index]; index--) { ; }

    return index;
}


static FT817BAND_t band; 


void FT817Band(uint16_t adc)
{
    FT817BAND_t new;

    if(band != (new = GetIndexWithHysteresis(band, adc, upThre, downThre, sizeof(upThre)/sizeof(upThre[0])))) {
        FC757ATBandNone();
        __delay_ms(50);
        FC757ATChangeBand(band = new);
    }
}


void FC757ATBandNone(void)
{
    Seg7DispClearNum();
}

void FC757ATChangeBand(FT817BAND_t band)
{
    switch(band) {
    case FT817BAND_THRU:
    // case FT817BAND_50M:
    // case FT817BAND_144M: 
    // case FT817BAND_430M: 
        Seg7DispClearNum();
        break;
    default:
        Seg7DispHex(band);
        break;
    }
}


/*++++++++++++++++++++++
#include <stdio.h>

static uint16_t Volt2adData(double volt)
{
    double tmp = volt*ADC_MAX/REF_VOLT; 
    if(ADC_MAX < tmp)	{ tmp = ADC_MAX; }
    
    return tmp;		
}


int main(int argc, char* argv[])
{
    int i;
    FT817BAND_t band = 0, newBand;

    double volt;

    while(EOF != scanf("%lf", &volt)) {
        if(band != (newBand = GetIndexWithHysteresis(band, Volt2adData(volt), upThre, downThre, sizeof(upThre)/sizeof(upThre[0])))) {
            band = newBand;
            printf("band = %d\n", band);
        }
    }

    return 0;
}

++++++++++++++++++++++*/
