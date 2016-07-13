/* 
 * File:   seg7_disp.h
 * Author: ikeda
 *
 * Created on 2015/01/17, 17:58
 */

#ifndef SEG7_DISP_H
#define	SEG7_DISP_H


#include <stdbool.h>


#ifdef	__cplusplus
extern "C" {
#endif
 
extern void Seg7DispHex(int n);
extern void Seg7DotOn(bool on);
extern int Seg7DotIsOn(void);
extern void Seg7DispClearNum(void);



#ifdef	__cplusplus
}
#endif

#endif	/* SEG7_DISP_H */

