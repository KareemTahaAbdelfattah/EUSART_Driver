/* 
 * File:   ccp.c
 * Author: Kareem Taha
 *
 * Created on November 19, 2022, 3:25 PM
 */



 /* Section : Includes */
#include "ccp_hal.h"

 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */
#if CCP1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
static void(*CCP1_InterruptHandler)(void) = NULL;
#endif


#if CCP2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
static void(*CCP2_InterruptHandler)(void) = NULL;
#endif

static STD_ReturnType CCP_CAPTURE_TIMER_SELECT(const ccp_t *_ccp1_object);

STD_ReturnType CCP_Init(const ccp_t *_ccp1_object){
    STD_ReturnType ret = E_OK;
    if(_ccp1_object == NULL) ret = E_NOT_OK;
    else{
        /*Disable CCP*/
        if(_ccp1_object->ccp_inst == CCP1_INST) CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        else CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
        /*Initialize Pin of CCP*/
        gpio_pin_direction_init(&(_ccp1_object->pin_ccp));
        /*Enable CCP1 with Configuration*/
        if(_ccp1_object->ccp_mode == CCP_PWM_MODE_){
            #if(CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE)
            if(CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE && _ccp1_object->ccp_inst == CCP1_INST) CCP1CONbits.CCP1M = CCP_PWM_MODE;
            else CCP2CONbits.CCP2M = CCP_PWM_MODE;
            /*initialize PWM FREQ*/
            PR2 = (uint8)((_XTAL_FREQ / ((_ccp1_object->PWM_Frequency) * 4.0 * (_ccp1_object->timer2_postscaler) *
                    (_ccp1_object->timer2_prescaler))) - 1);
            #endif
        }
        else if(_ccp1_object->ccp_mode == CCP_CAPTURE_MODE){
            if(_ccp1_object->ccp_inst == CCP1_INST){
                switch(_ccp1_object->ccp_mode_varient){
                    case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                        CCP1CONbits.CCP1M = CCP_CAPTURE_MODE_1_FALLING_EDGE;
                        break;
                    case CCP_CAPTURE_MODE_1_RAISING_EDGE:
                        CCP1CONbits.CCP1M = CCP_CAPTURE_MODE_1_RAISING_EDGE;
                        break;
                    case CCP_CAPTURE_MODE_4_RAISING_EDGE:
                        CCP1CONbits.CCP1M = CCP_CAPTURE_MODE_4_RAISING_EDGE;
                        break;
                    case CCP_CAPTURE_MODE_16_RAISING_EDGE:
                        CCP1CONbits.CCP1M = CCP_CAPTURE_MODE_16_RAISING_EDGE;
                        break;
                    default:
                        break;
                }
            }
            else if(_ccp1_object->ccp_inst == CCP2_INST){
                switch(_ccp1_object->ccp_mode_varient){
                    case CCP_CAPTURE_MODE_1_FALLING_EDGE:
                        CCP2CONbits.CCP2M = CCP_CAPTURE_MODE_1_FALLING_EDGE;
                        break;
                    case CCP_CAPTURE_MODE_1_RAISING_EDGE:
                        CCP2CONbits.CCP2M = CCP_CAPTURE_MODE_1_RAISING_EDGE;
                        break;
                    case CCP_CAPTURE_MODE_4_RAISING_EDGE:
                        CCP2CONbits.CCP2M = CCP_CAPTURE_MODE_4_RAISING_EDGE;
                        break;
                    case CCP_CAPTURE_MODE_16_RAISING_EDGE:
                        CCP2CONbits.CCP2M = CCP_CAPTURE_MODE_16_RAISING_EDGE;
                        break;
                    default:
                        break;
                }
            }
            CCP_CAPTURE_TIMER_SELECT(_ccp1_object);
        }
        else if(_ccp1_object->ccp_mode == CCP_COMPARE_MODE){
            if(_ccp1_object->ccp_inst == CCP1_INST){
                switch(_ccp1_object->ccp_mode_varient){
                    case CCP_COMPARE_MODE_SET_PIN_LOW:
                        CCP1CONbits.CCP1M = CCP_COMPARE_MODE_SET_PIN_LOW;
                        break;
                    case CCP_COMPARE_MODE_SET_PIN_HIGH:
                        CCP1CONbits.CCP1M = CCP_COMPARE_MODE_SET_PIN_HIGH;
                        break;
                    case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
                        CCP1CONbits.CCP1M = CCP_COMPARE_MODE_TOGGLE_ON_MATCH;
                        break;
                    case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                        CCP1CONbits.CCP1M = CCP_COMPARE_MODE_GEN_SW_INTERRUPT;
                        break;
                    case CCP_COMPARE_MODE_GEN_SW_EVENT:
                        CCP1CONbits.CCP1M = CCP_COMPARE_MODE_GEN_SW_EVENT;
                        break; 
                    default:
                        break;
                }
            }
            else if(_ccp1_object->ccp_inst == CCP2_INST){
                switch(_ccp1_object->ccp_mode_varient){
                    case CCP_COMPARE_MODE_SET_PIN_LOW:
                        CCP2CONbits.CCP2M = CCP_COMPARE_MODE_SET_PIN_LOW;
                        break;
                    case CCP_COMPARE_MODE_SET_PIN_HIGH:
                        CCP2CONbits.CCP2M = CCP_COMPARE_MODE_SET_PIN_HIGH;
                        break;
                    case CCP_COMPARE_MODE_TOGGLE_ON_MATCH:
                        CCP2CONbits.CCP2M = CCP_COMPARE_MODE_TOGGLE_ON_MATCH;
                        break;
                    case CCP_COMPARE_MODE_GEN_SW_INTERRUPT:
                        CCP2CONbits.CCP2M = CCP_COMPARE_MODE_GEN_SW_INTERRUPT;
                        break;
                    case CCP_COMPARE_MODE_GEN_SW_EVENT:
                        CCP2CONbits.CCP2M = CCP_COMPARE_MODE_GEN_SW_EVENT;
                        break; 
                    default:
                        break;
                }
            }
            CCP_CAPTURE_TIMER_SELECT(_ccp1_object);
        }
        
        if(_ccp1_object->ccp_inst == CCP1_INST){
            /*interrupt configuration*/
            #if CCP1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
            CCP1_Interrupt_Enable();
            CCP1_Interrupt_Flag_Clear();
            CCP1_InterruptHandler = (_ccp1_object->CCP1_InterruptHandler);
            #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
            Interrupt_PriorityLevelsEnable();
            if(_ccp1_object->priority_ccp1 == INTERRUPT_High_Priority){
                Interrupt_GlobalInterruptHighEnable();
                CCP1_Interrupt_Priority_High();
            }
            else{
                Interrupt_GlobalInterruptLowEnable();
                CCP1_Interrupt_Priority_Low();
            }
            #else
            /*Enable Global Interrupt */
            Interrupt_GlobalInterruptEnable();
            /*Enable Peripherals Interrupt */
            Interrupt_PeripheralInterruptEnable();
            #endif
            #endif
        }
        else{
            /*interrupt configuration*/
            #if CCP2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
            CCP2_Interrupt_Enable();
            CCP2_Interrupt_Flag_Clear();
            CCP2_InterruptHandler = (_ccp1_object->CCP2_InterruptHandler);
            #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
            Interrupt_PriorityLevelsEnable();
            if(_ccp1_object->priority_ccp2 == INTERRUPT_High_Priority){
                Interrupt_GlobalInterruptHighEnable();
                CCP2_Interrupt_Priority_High();
            }
            else{
                Interrupt_GlobalInterruptLowEnable();
                CCP2_Interrupt_Priority_Low();
            }
            #else
            /*Enable Global Interrupt */
            Interrupt_GlobalInterruptEnable();
            /*Enable Peripherals Interrupt */
            Interrupt_PeripheralInterruptEnable();
            #endif
            #endif
        }
    }
    return ret;
}

STD_ReturnType CCP_DeInit(const ccp_t *_ccp1_object){
    STD_ReturnType ret = E_OK;
    if(_ccp1_object == NULL) ret = E_NOT_OK;
    else{
        /*Disable CCP1*/
        if(_ccp1_object->ccp_inst == CCP1_INST){
            CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
            #if CCP1_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
            CCP1_Interrupt_Disable();
            #endif
        }
        else{
            CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
            #if CCP2_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
            CCP2_Interrupt_Disable();
            #endif
        }
    }
    return ret;  
}

#if(CCP1_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_PWM_MODE)
STD_ReturnType CCP_PWM_Set_Duty(const ccp_t *_ccp1_object ,const uint8 _duty){
    STD_ReturnType ret = E_OK;
    uint16 l_duty_temp = 0;
    if(_ccp1_object == NULL) ret = E_NOT_OK;
    else{
        if(_ccp1_object->ccp_inst == CCP1_INST) {
            l_duty_temp = (uint16)((PR2 + 1) * (_duty / 100.0) * 4.0);
            CCP1CONbits.DC1B = (uint8)(l_duty_temp & 0x0003);
            CCPR1L = (uint8)(l_duty_temp >> 2);
        }
        else{
            l_duty_temp = (uint16)((PR2 + 1) * (_duty / 100.0) * 4.0);
            CCP2CONbits.DC2B = (uint8)(l_duty_temp & 0x0003);
            CCPR2L = (uint8)(l_duty_temp >> 2);
        }
    }
    return ret;
}
STD_ReturnType CCP_PWM_Start(const ccp_t *_ccp1_object){
    STD_ReturnType ret = E_OK;
    if(_ccp1_object == NULL) ret = E_NOT_OK;
    else{
        if(_ccp1_object->ccp_inst == CCP1_INST) CCP1CONbits.CCP1M = CCP_PWM_MODE;
        else CCP2CONbits.CCP2M = CCP_PWM_MODE;
    }
    return ret;
}
STD_ReturnType CCP_PWM_Stop(const ccp_t *_ccp1_object){
    STD_ReturnType ret = E_OK;
    if(_ccp1_object == NULL) ret = E_NOT_OK;
    else{
        if(_ccp1_object->ccp_inst == CCP1_INST) CCP1CONbits.CCP1M = CCP_MODULE_DISABLE;
        else CCP2CONbits.CCP2M = CCP_MODULE_DISABLE;
    }
    return ret;
}
#endif


#if(CCP1_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_CAPTURE_MODE)

STD_ReturnType CCP_IsCaptureDataReady(const ccp_t *_ccp1_object, uint8 *capture_status){
    STD_ReturnType ret = E_OK;
    if(capture_status == NULL || _ccp1_object == NULL) ret = E_NOT_OK;
    else{
        if(_ccp1_object->ccp_inst == CCP1_INST){
            if(PIR1bits.CCP1IF == CCP1_CAPTURE_READY){
                CCP1_Interrupt_Flag_Clear();
                *capture_status = CCP1_CAPTURE_READY;

            }else{
                *capture_status = CCP1_CAPTURE_NOT_READY;
            }
        }
        else if(_ccp1_object->ccp_inst == CCP2_INST){
            if(PIR2bits.CCP2IF == CCP2_CAPTURE_READY){
                CCP2_Interrupt_Flag_Clear();
                *capture_status = CCP2_CAPTURE_READY;

            }else{
                *capture_status = CCP2_CAPTURE_NOT_READY;
            }
        }
    }
    return ret;
}
STD_ReturnType CCP_CaptureMode_Read_Value(const ccp_t *_ccp1_object, uint16 *capture_value){
    STD_ReturnType ret = E_OK;
    if(_ccp1_object == NULL || capture_value == NULL) ret = E_NOT_OK;
    else{
        ccp_reg_t capture_temporary_values = {.ccpr_low = 0, .ccpr_high = 0};
        if(_ccp1_object->ccp_inst == CCP1_INST){
            capture_temporary_values.ccpr_low = CCPR1L;
            capture_temporary_values.ccpr_high = CCPR1H;
        }
        else if(_ccp1_object->ccp_inst == CCP2_INST){
            capture_temporary_values.ccpr_low = CCPR2L;
            capture_temporary_values.ccpr_high = CCPR2H;
        }
        *capture_value = capture_temporary_values.ccpr_16bit;
    }
    return ret;
}
#endif



#if(CCP1_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE) || (CCP2_CFG_MODE_SELECTED == CCP_CFG_COMPARE_MODE)
STD_ReturnType CCP_IsCompareCompelete(const ccp_t *_ccp1_object, uint8 *compare_status){
    STD_ReturnType ret = E_OK;
    if(compare_status == NULL || _ccp1_object == NULL) ret = E_NOT_OK;
    else{
        if(_ccp1_object->ccp_inst == CCP1_INST){
            if(PIR1bits.CCP1IF == CCP1_COMPARE_READY){
                CCP1_Interrupt_Flag_Clear();
                *compare_status = CCP1_COMPARE_READY;

            }else{
                *compare_status = CCP1_COMPARE_NOT_READY;
            }
        }
        else if(_ccp1_object->ccp_inst == CCP2_INST){
            if(PIR2bits.CCP2IF == CCP2_COMPARE_READY){
                CCP2_Interrupt_Flag_Clear();
                *compare_status = CCP2_COMPARE_READY;

            }else{
                *compare_status = CCP2_COMPARE_NOT_READY;
            }
        }
    }
    return ret;
}

STD_ReturnType CCP_CompareMode_set_Value(const ccp_t *_ccp1_object, uint16 compare_value){
    STD_ReturnType ret = E_OK;
    if(_ccp1_object == NULL) ret = E_NOT_OK;
    else{
        ccp_reg_t capture_temporary_values = {.ccpr_low = 0, .ccpr_high = 0};
        capture_temporary_values.ccpr_16bit = compare_value;
        if(_ccp1_object->ccp_inst == CCP1_INST){
            CCPR1L = capture_temporary_values.ccpr_low;
            CCPR1H = capture_temporary_values.ccpr_high;
        }
        else if(_ccp1_object->ccp_inst == CCP2_INST){
            CCPR2L = capture_temporary_values.ccpr_low;
            CCPR2H = capture_temporary_values.ccpr_high;
        }
    }
    return ret;
}

#endif



static STD_ReturnType CCP_CAPTURE_TIMER_SELECT(const ccp_t *_ccp1_object){
    STD_ReturnType ret = E_OK;
    if(_ccp1_object == NULL) ret = E_NOT_OK;
    else{
        if(_ccp1_object->ccp_capture_timer == CCP1_CCP2_TIMER3){
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 1;
        }
        else if(_ccp1_object->ccp_capture_timer == CCP2_TIMER3_CCP1_TIMER1){
            T3CONbits.T3CCP1 = 1;
            T3CONbits.T3CCP2 = 0;
        }
        else if(_ccp1_object->ccp_capture_timer == CCP1_CCP2_TIMER1){
            T3CONbits.T3CCP1 = 0;
            T3CONbits.T3CCP2 = 0;
        }
    }
    return ret;
}

void CCP1_ISR(void){
    CCP1_Interrupt_Flag_Clear();
    if(CCP1_InterruptHandler){
        CCP1_InterruptHandler();
    }
}



void CCP2_ISR(void){
    CCP2_Interrupt_Flag_Clear();
    if(CCP2_InterruptHandler){
        CCP2_InterruptHandler();
    }
}