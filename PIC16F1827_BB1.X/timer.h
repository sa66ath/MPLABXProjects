/* 
 * File:   timer.h
 * Author: ikeda
 *
 * Created on 2015/01/21, 10:10
 */

#ifndef TIMER_H
#define	TIMER_H

#include <stdbool.h>

#ifdef	__cplusplus
extern "C" {
#endif


extern void TimerInit(void);
extern void TimerStart(void);
extern bool TimerSys1msElasped(unsigned long interval, unsigned long *saved);
extern void TimerIncSys1ms(void);
extern unsigned long TimerGetSys1ms(void);


#ifdef	__cplusplus
}
#endif

#endif	/* TIMER_H */

