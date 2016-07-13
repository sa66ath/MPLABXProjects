/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

extern void InitApp(void);         /* I/O and Peripheral Initialization */

extern void Timer0_Init(void);
extern void ADC_Init(void);
extern unsigned char ADC_Convert(void);
