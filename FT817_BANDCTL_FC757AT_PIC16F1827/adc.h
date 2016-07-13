/* 
 * File:   adc.h
 * Author: ikeda
 *
 * Created on 2015/01/20, 16:54
 */

#ifndef ADC_H
#define	ADC_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/* adc.c */
extern void FVRInit(void);
extern void AdcInit(void);
extern void AdcStart(void);
extern uint16_t AdcRead(void);
extern void AdcIsr(void);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

