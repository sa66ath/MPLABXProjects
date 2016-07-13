/* 
 * File:   pwm.h
 * Author: ikeda
 *
 * Created on 2015/01/21, 15:03
 */

#ifndef PWM_H
#define	PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

void PwmInit(void);
void PwmDuty(uint16_t val);

#ifdef	__cplusplus
}
#endif

#endif	/* PWM_H */

