/* 
 * File:   ccp1_hal.h
 * Author: Kareem Taha
 *
 * Created on November 19, 2022, 3:25 PM
 */

#ifndef CCP1_HAL_H
#define	CCP1_HAL_H


 /* Section : Includes */
#include "../hal_gpio.h"
#include "../std_types.h"
#include "pic18f4620.h"
#include "../Interrupt/hal_internal_interrupt.h"
#include "ccp_hal_cfg.h"
 /* Section : Macros Definition */

/* CCP1 Capture Mode State*/
#define CCP1_CAPTURE_NOT_READY      0x00
#define CCP1_CAPTURE_READY          0x01


/* CCP1 Compare Mode State*/
#define CCP1_COMPARE_NOT_READY      0x00
#define CCP1_COMPARE_READY          0x01


/* CCP2 Capture Mode State*/
#define CCP2_CAPTURE_NOT_READY      0x00
#define CCP2_CAPTURE_READY          0x01


/* CCP2 Compare Mode State*/
#define CCP2_COMPARE_NOT_READY      0x00
#define CCP2_COMPARE_READY          0x01

/*Post-Scalar of TIMER2*/
#define CCP_TIMER2_POSTSCALER_DIV_BY_1           1
#define CCP_TIMER2_POSTSCALER_DIV_BY_2           2
#define CCP_TIMER2_POSTSCALER_DIV_BY_3           3
#define CCP_TIMER2_POSTSCALER_DIV_BY_4           4
#define CCP_TIMER2_POSTSCALER_DIV_BY_5           5
#define CCP_TIMER2_POSTSCALER_DIV_BY_6           6
#define CCP_TIMER2_POSTSCALER_DIV_BY_7           7
#define CCP_TIMER2_POSTSCALER_DIV_BY_8           8
#define CCP_TIMER2_POSTSCALER_DIV_BY_9           9
#define CCP_TIMER2_POSTSCALER_DIV_BY_10          10
#define CCP_TIMER2_POSTSCALER_DIV_BY_11          11
#define CCP_TIMER2_POSTSCALER_DIV_BY_12          12
#define CCP_TIMER2_POSTSCALER_DIV_BY_13          13
#define CCP_TIMER2_POSTSCALER_DIV_BY_14          14
#define CCP_TIMER2_POSTSCALER_DIV_BY_15          15
#define CCP_TIMER2_POSTSCALER_DIV_BY_16          16


/*Pre-Scalar of TIMER2*/
#define CCP_TIMER2_PRESCALER_DIV_BY_1           1
#define CCP_TIMER2_PRESCALER_DIV_BY_4           4
#define CCP_TIMER2_PRESCALER_DIV_BY_16          16


/*CCP1M Register Select MODE*/
#define CCP_MODULE_DISABLE                  (uint8)0x00
#define CCP_CAPTURE_MODE_1_FALLING_EDGE     (uint8)0x04
#define CCP_CAPTURE_MODE_1_RAISING_EDGE     (uint8)0x05
#define CCP_CAPTURE_MODE_4_RAISING_EDGE     (uint8)0x06
#define CCP_CAPTURE_MODE_16_RAISING_EDGE    (uint8)0x07
#define CCP_COMPARE_MODE_SET_PIN_LOW        (uint8)0x08
#define CCP_COMPARE_MODE_SET_PIN_HIGH       (uint8)0x09
#define CCP_COMPARE_MODE_TOGGLE_ON_MATCH    (uint8)0x02
#define CCP_COMPARE_MODE_GEN_SW_INTERRUPT   (uint8)0x0A
#define CCP_COMPARE_MODE_GEN_SW_EVENT       (uint8)0x0B
#define CCP_PWM_MODE                        (uint8)0x0C


 /* Section : Macros Functions Declaration */


#define CCP1_SET_MODE(_CONFIG)              (CCP1CONbits.CCP1M = _CONFIG)
#define CCP2_SET_MODE(_CONFIG)              (CCP2CONbits.CCP2M = _CONFIG)
 /* Section : Data Types Declaration */


typedef enum{
    CCP_PWM_MODE_ = 0,
    CCP_CAPTURE_MODE,
    CCP_COMPARE_MODE,
}ccp_mode_t;


typedef union{
    struct{
        uint8 ccpr_low;
        uint8 ccpr_high;
    };
    struct{
        uint16 ccpr_16bit;
    };
}ccp_reg_t;

typedef enum{
    CCP1_INST = 0,
    CCP2_INST
}ccp_inst_t;


typedef enum{
    CCP1_CCP2_TIMER3 = 0,
    CCP2_TIMER3_CCP1_TIMER1,
    CCP1_CCP2_TIMER1,
}ccp_capture_timer_t;

typedef struct {
    ccp_inst_t ccp_inst;
    ccp_mode_t ccp_mode;
    uint8 ccp_mode_varient;
    pin_config_t pin_ccp;
    ccp_capture_timer_t ccp_capture_timer;
    #if CCP1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
    void(*CCP1_InterruptHandler)(void);
    Interrupt_Priority_cfg priority_ccp1;
    #endif 
    #if CCP2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
    void(*CCP2_InterruptHandler)(void);
    Interrupt_Priority_cfg priority_ccp2;
    #endif 
    #if(CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE)
    uint32 PWM_Frequency;
    uint8 timer2_postscaler: 4; 
    uint8 timer2_prescaler: 2; 
    #endif    
}ccp_t;

 /* Section : Function Declaration */

STD_ReturnType CCP_Init(const ccp_t *_ccp1_object);
STD_ReturnType CCP_DeInit(const ccp_t *_ccp1_object);

#if(CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE || CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE)
STD_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp1_object ,const uint8 _duty);
STD_ReturnType CCP_PWM_Start(const ccp_t *_ccp1_object);
STD_ReturnType CCP_PWM_Stop(const ccp_t *_ccp1_object);
#endif


#if(CCP1_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE)
STD_ReturnType CCP_IsCaptureDataReady(const ccp_t *_ccp1_object ,uint8 *capture_status);
STD_ReturnType CCP_CaptureMode_Read_Value(const ccp_t *_ccp1_object, uint16 *capture_value);
#endif



#if(CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE)
STD_ReturnType CCP_IsCompareCompelete(const ccp_t *_ccp1_object, uint8 *compare_status);
STD_ReturnType CCP_CompareMode_set_Value(const ccp_t *_ccp1_object, uint16 compare_value);
#endif



#endif	/* CCP1_HAL_H */

