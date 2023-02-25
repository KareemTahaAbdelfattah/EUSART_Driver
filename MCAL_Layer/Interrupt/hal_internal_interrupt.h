/* 
 * File:   hal_internal_interrupt.h
 * Author: Kareem Taha
 *
 * Created on October 6, 2022, 1:47 PM
 */

#ifndef HAL_INTERRUPT_H
#define	HAL_INTERRUPT_H

 /* Section : Includes */

#include "hal_interrupt_cfg.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

/*________________________ ADC ____________________*/

#if ADC_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for ADC module */
#define ADC_Interrupt_Disable()                (PIE1bits.ADIE = 0)
/* set interrupt enable for ADC module */
#define ADC_Interrupt_Enable()                 (PIE1bits.ADIE = 1)
/* clear interrupt flag for ADC module */
#define ADC_Interrupt_Flag_Clear()             (PIR1bits.ADIF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set ADC module interrupt -> high priority */
#define ADC_Interrupt_Priority_High()          (IPR1bits.ADIP = 1)
/* set ADC module interrupt -> low priority */
#define ADC_Interrupt_Priority_Low()           (IPR1bits.ADIP = 0)
#endif

#endif



/*________________________ TIMER0 ____________________*/

#if TIMER0_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for TIMER0 module */
#define TIMER0_Interrupt_Disable()                (INTCONbits.TMR0IE = 0)
/* set interrupt enable for TIMER0 module */
#define TIMER0_Interrupt_Enable()                 (INTCONbits.TMR0IE = 1)
/* clear interrupt flag for TIMER0 module */
#define TIMER0_Interrupt_Flag_Clear()             (INTCONbits.TMR0IF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set TIMER0 module interrupt -> high priority */
#define TIMER0_Interrupt_Priority_High()          (INTCON2bits.TMR0IP = 1)
/* set TIMER0 module interrupt -> low priority */
#define TIMER0_Interrupt_Priority_Low()           (INTCON2bits.TMR0IP = 0)
#endif

#endif



/*________________________ TIMER1 ____________________*/

#if TIMER1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for TIMER1 module */
#define TIMER1_Interrupt_Disable()                (PIE1bits.TMR1IE = 0)
/* set interrupt enable for TIMER1 module */
#define TIMER1_Interrupt_Enable()                 (PIE1bits.TMR1IE = 1)
/* clear interrupt flag for TIMER1 module */
#define TIMER1_Interrupt_Flag_Clear()             (PIR1bits.TMR1IF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set TIMER1 module interrupt -> high priority */
#define TIMER1_Interrupt_Priority_High()          (IPR1bits.TMR1IP = 1)
/* set TIMER1 module interrupt -> low priority */
#define TIMER1_Interrupt_Priority_Low()           (IPR1bits.TMR1IP = 0)
#endif

#endif





/*________________________ TIMER2 ____________________*/

#if TIMER2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for TIMER2 module */
#define TIMER2_Interrupt_Disable()                (PIE1bits.TMR2IE = 0)
/* set interrupt enable for TIMER2 module */
#define TIMER2_Interrupt_Enable()                 (PIE1bits.TMR2IE = 1)
/* clear interrupt flag for TIMER2 module */
#define TIMER2_Interrupt_Flag_Clear()             (PIR1bits.TMR2IF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set TIMER2 module interrupt -> high priority */
#define TIMER2_Interrupt_Priority_High()          (IPR1bits.TMR2IP = 1)
/* set TIMER2 module interrupt -> low priority */
#define TIMER2_Interrupt_Priority_Low()           (IPR1bits.TMR2IP = 0)
#endif

#endif




/*________________________ TIMER3 ____________________*/

#if TIMER3_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for TIMER3 module */
#define TIMER3_Interrupt_Disable()                (PIE2bits.TMR3IE = 0)
/* set interrupt enable for TIMER3 module */
#define TIMER3_Interrupt_Enable()                 (PIE2bits.TMR3IE = 1)
/* clear interrupt flag for TIMER3 module */
#define TIMER3_Interrupt_Flag_Clear()             (PIR2bits.TMR3IF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set TIMER3 module interrupt -> high priority */
#define TIMER3_Interrupt_Priority_High()          (IPR2bits.TMR3IP = 1)
/* set TIMER3 module interrupt -> low priority */
#define TIMER3_Interrupt_Priority_Low()           (IPR2bits.TMR3IP = 0)
#endif

#endif



/*________________________ CCP1 ____________________*/

#if CCP1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for CCP1 module */
#define CCP1_Interrupt_Disable()                (PIE1bits.CCP1IE = 0)
/* set interrupt enable for CCP1 module */
#define CCP1_Interrupt_Enable()                 (PIE1bits.CCP1IE = 1)
/* clear interrupt flag for CCP1 module */
#define CCP1_Interrupt_Flag_Clear()             (PIR1bits.CCP1IF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set CCP1 module interrupt -> high priority */
#define CCP1_Interrupt_Priority_High()          (IPR1bits.CCP1IP = 1)
/* set CCP1 module interrupt -> low priority */
#define CCP1_Interrupt_Priority_Low()           (IPR1bits.CCP1IP = 0)
#endif

#endif



/*________________________ CCP2 ____________________*/

#if CCP2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for CCP2 module */
#define CCP2_Interrupt_Disable()                (PIE2bits.CCP2IE = 0)
/* set interrupt enable for CCP2 module */
#define CCP2_Interrupt_Enable()                 (PIE2bits.CCP2IE = 1)
/* clear interrupt flag for CCP2 module */
#define CCP2_Interrupt_Flag_Clear()             (PIR2bits.CCP2IF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set CCP2 module interrupt -> high priority */
#define CCP2_Interrupt_Priority_High()          (IPR2bits.CCP2IP = 1)
/* set CCP2 module interrupt -> low priority */
#define CCP2_Interrupt_Priority_Low()           (IPR2bits.CCP2IP = 0)
#endif

#endif




/*________________________ EUSART_TX ____________________*/

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for EUSART_TX module */
#define EUSART_TX_Interrupt_Disable()                (PIE1bits.TXIE = 0)
/* set interrupt enable for EUSART_TX module */
#define EUSART_TX_Interrupt_Enable()                 (PIE1bits.TXIE = 1)
/* clear interrupt flag for EUSART_TX module */
//#define EUSART_TX_Interrupt_Flag_Clear()             (PIR1bits.TXIF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set EUSART_TX module interrupt -> high priority */
#define EUSART_TX_Interrupt_Priority_High()          (IPR1bits.TXIP = 1)
/* set EUSART_TX module interrupt -> low priority */
#define EUSART_TX_Interrupt_Priority_Low()           (IPR1bits.TXIP = 0)
#endif

#endif


/*________________________ EUSART_RX ____________________*/

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
/* clear interrupt enable for EUSART_RX module */
#define EUSART_RX_Interrupt_Disable()                (PIE1bits.RCIE = 0)
/* set interrupt enable for EUSART_RX module */
#define EUSART_RX_Interrupt_Enable()                 (PIE1bits.RCIE = 1)
/* clear interrupt flag for EUSART_RX module */
//#define EUSART_RX_Interrupt_Flag_Clear()             (PIR1bits.RCIF = 0)

#if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
/* set EUSART_RX module interrupt -> high priority */
#define EUSART_RX_Interrupt_Priority_High()          (IPR1bits.RCIP = 1)
/* set EUSART_RX module interrupt -> low priority */
#define EUSART_RX_Interrupt_Priority_Low()           (IPR1bits.RCIP = 0)
#endif

#endif
 /* Section : Data Types Declaration */

 /* Section : Function Declaration */

#endif	/* HAL_INTERRUPT_H */

