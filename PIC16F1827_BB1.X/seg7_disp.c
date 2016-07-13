#include <xc.h>

#include <stdint.h>        /* For uint8_t definition */
#include <stdbool.h>


#define SEG7_A_BIT  _LATA_LATA7_POSITION
#define SEG7_B_BIT  _LATA_LATA6_POSITION
#define SEG7_C_BIT  _LATA_LATA3_POSITION
#define SEG7_D_BIT  _LATA_LATA2_POSITION
#define SEG7_F_BIT  _LATA_LATA0_POSITION
#define SEG7_G_BIT  _LATA_LATA1_POSITION

#define SEG7_A_MASK (0x01<<SEG7_A_BIT) 
#define SEG7_B_MASK (0x01<<SEG7_B_BIT) 
#define SEG7_C_MASK (0x01<<SEG7_C_BIT) 
#define SEG7_D_MASK (0x01<<SEG7_D_BIT) 
#define SEG7_F_MASK (0x01<<SEG7_F_BIT) 
#define SEG7_G_MASK (0x01<<SEG7_G_BIT) 


#define SEG7_DP_BIT _LATA_LATA4_POSITION
#define SEG7_DP_MASK    (0x01<<SEG7_DP_BIT)


#define SEG7_E_BIT  _LATB_LATB5_POSITION
#define SEG7_E_MASK     (0x01<<SEG7_E_BIT)

#define SEG7_EX_BIT 4 
#define SEG7_EX_MASK    (0x01<<SEG7_EX_BIT)


#define SEG7_PORTA_MASK (SEG7_A_MASK | SEG7_B_MASK | SEG7_C_MASK | SEG7_D_MASK | SEG7_F_MASK | SEG7_G_MASK | SEG7_DP_MASK)
#define SEG7_PORTB_MASK SEG7_E_MASK

#define SEG7_PORTA_NUM_MASK (~SEG7_DP_MASK & SEG7_PORTA_MASK)
#define SEG7_PORTB_NUM_MASK SEG7_PORTB_MASK

const uint8_t portNumPat[] = { /* 0=lit, 1=dim */
    {       /* 0 */
        0<<SEG7_A_BIT |
        0<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        0<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        1<<SEG7_G_BIT
    },
    {       /* 1 */
        1<<SEG7_A_BIT |
        0<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        1<<SEG7_D_BIT |
        1<<SEG7_EX_BIT |
        1<<SEG7_F_BIT |
        1<<SEG7_G_BIT
    },
    {       /* 2 */
        0<<SEG7_A_BIT |
        0<<SEG7_B_BIT |
        1<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        0<<SEG7_EX_BIT |
        1<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* 3 */
        0<<SEG7_A_BIT |
        0<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        1<<SEG7_EX_BIT |
        1<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* 4 */
        1<<SEG7_A_BIT |
        0<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        1<<SEG7_D_BIT |
        1<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* 5 */
        0<<SEG7_A_BIT |
        1<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        1<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* 6 */
        0<<SEG7_A_BIT |
        1<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        0<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* 7 */
        0<<SEG7_A_BIT |
        0<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        1<<SEG7_D_BIT |
        1<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        1<<SEG7_G_BIT
    },
    {       /* 8 */
        0<<SEG7_A_BIT |
        0<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        0<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* 9 */
        0<<SEG7_A_BIT |
        0<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        1<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* A */
        0<<SEG7_A_BIT |
        0<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        1<<SEG7_D_BIT |
        0<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* B */
        1<<SEG7_A_BIT |
        1<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        0<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* C */
        0<<SEG7_A_BIT |
        1<<SEG7_B_BIT |
        1<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        0<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        1<<SEG7_G_BIT
    },
    {       /* D */
        1<<SEG7_A_BIT |
        0<<SEG7_B_BIT |
        0<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        0<<SEG7_EX_BIT |
        1<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* E */
        0<<SEG7_A_BIT |
        1<<SEG7_B_BIT |
        1<<SEG7_C_BIT |
        0<<SEG7_D_BIT |
        0<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    },
    {       /* F */
        0<<SEG7_A_BIT |
        1<<SEG7_B_BIT |
        1<<SEG7_C_BIT |
        1<<SEG7_D_BIT |
        0<<SEG7_EX_BIT |
        0<<SEG7_F_BIT |
        0<<SEG7_G_BIT
    }
};


void Seg7DispHex(int n)
{
    LATA = (SEG7_DP_MASK & LATA) | (SEG7_PORTA_NUM_MASK & portNumPat[n]); 
    LATB = (~SEG7_E_MASK & LATB) | ((SEG7_EX_MASK & portNumPat[n])? SEG7_E_MASK:0x00);
}

void Seg7DotOn(bool on)
{
    LATA = (~SEG7_DP_MASK & LATA) | ((on)? 0x00:SEG7_DP_MASK);
}

int Seg7DotIsOn(void)
{
   return !(SEG7_DP_MASK & LATA); 
}

void Seg7DispClearNum(void)
{
    LATA |= SEG7_PORTA_NUM_MASK;
    LATB |= SEG7_PORTB_NUM_MASK;
}
