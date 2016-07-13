/* 
 * File:   ft817band.h
 * Author: ikeda
 *
 * Created on 2015/01/31, 16:48
 */

#ifndef FT817BAND_H
#define	FT817BAND_H


#include <stddef.h>

typedef enum {
    FT817BAND_THRU, 
    FT817BAND_1_9M, 
    FT817BAND_3_5M, 
    FT817BAND_7M, 
    FT817BAND_10M, 
    FT817BAND_14M, 
    FT817BAND_18M, 
    FT817BAND_21M, 
    FT817BAND_24_5M, 
    FT817BAND_28M, 
    FT817BAND_50M, 
    FT817BAND_144M, 
    FT817BAND_430M, 
    NUMOF_FT817BAND, 
} FT817BAND_t;



#ifdef	__cplusplus
extern "C" {
#endif


extern size_t GetIndexWithHysteresis(size_t index, uint16_t val, const uint16_t *upTbl, const uint16_t *downTbl, size_t tblSize);
extern void FT817Band(uint16_t adc);
extern void FC757ATBandNone(void);
extern void FC757ATChangeBand(FT817BAND_t band);


#ifdef	__cplusplus
}
#endif

#endif	/* FT817BAND_H */

