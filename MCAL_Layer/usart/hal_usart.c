/* 
 * File:   hal_usart.c
 * Author: Kareem Taha
 *
 * Created on Feb 20, 2023, 8:50 PM
 */



 /* Section : Includes */
#include "hal_usart.h"


 /* Section : Macros Definition */

 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

 /* Section : Function Declaration */

#if EUSART_TX_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
static void(*EUSART_TX_InterruptHandler)(void) = NULL;
#endif

#if EUSART_RX_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
static void(*EUSART_RX_InterruptHandler)(void) = NULL;
static void(*EUSART_FramingErrorHandler)(void) = NULL;
static void(*EUSART_OverrunErrorHandler)(void) = NULL;
#endif

static void EUSART_BUADRATE_Calculation(const usart_t *_eusart);
static void eusart_async_tx_init(const usart_t *_eusart);
static void eusart_async_rx_init(const usart_t *_eusart);



STD_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart){
    STD_ReturnType ret = E_OK;
    if(_eusart == NULL) ret = E_NOT_OK;
    else{
      //disable usart  
      RCSTAbits.SPEN = EUSART_DISABLE;  
      TRISCbits.RC7 = 1;
      TRISCbits.RC6 = 1;
      /* make pin as an input*/
      EUSART_BUADRATE_Calculation(_eusart);
      eusart_async_tx_init(_eusart);
      eusart_async_rx_init(_eusart);
      //enable usart
      RCSTAbits.SPEN = EUSART_ENABLE; 
    }
    return ret;
}

STD_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart){
    STD_ReturnType ret = E_OK;
    if(_eusart == NULL) ret = E_NOT_OK;
    else{
        RCSTAbits.SPEN = EUSART_DISABLE;
    }
    return ret;

}
STD_ReturnType EUSART_ASYNC_ReadByte_Blocking(const usart_t *_eusart, uint8 *_data){
    STD_ReturnType ret = E_OK;
    if(_eusart == NULL) ret = E_NOT_OK;
    else{
        /*Blocking while register is empty*/
        while(!PIR1bits.RCIF);
        *(_data) = RCREG;
    }
    return ret;
}
STD_ReturnType EUSART_ASYNC_ReadByte_NonBlocking(const usart_t *_eusart, uint8 *_data){
    STD_ReturnType ret = E_OK;
    if(_eusart == NULL) ret = E_NOT_OK;
    else{
        if(PIR1bits.RCIF == 1) *(_data) = RCREG;
        else ret = E_NOT_OK;
        /*Blocking while register is empty*/
    }
    return ret;
}



STD_ReturnType EUSART_ASYNC_WriteByte_Blocking(const usart_t *_eusart, uint8 _data){
    STD_ReturnType ret = E_OK;
    if(_eusart == NULL) ret = E_NOT_OK;
    else{
        /*Blocking while register is not empty*/
        while(!TXSTAbits.TRMT);
        #if EUSART_TX_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
        PIE1bits.TXIE = 1;
        #endif
        TXREG = _data;
    }
    return ret;
}


STD_ReturnType EUSART_ASYNC_WriteString_Blocking(const usart_t *_eusart, uint8 *_data, uint32 str_len){
    STD_ReturnType ret = E_OK;
    if(_eusart == NULL) ret = E_NOT_OK;
    else{
        /*Send char by char*/
        for(uint32 char_counter = 0; char_counter < str_len; char_counter++){
            EUSART_ASYNC_WriteByte_Blocking(_eusart, _data[char_counter]);
        }
    }
    return ret;
}


static void EUSART_BUADRATE_Calculation(const usart_t *_eusart){
    float baud_rate_Temp = 0;
    switch(_eusart->buadrate_gen_cfg){
        case BUADRATE_ASYNC_8BIT_LOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNC_MODE;
            TXSTAbits.BRGH = EUSART_ASYNC_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
            baud_rate_Temp = ((_XTAL_FREQ / (float)(_eusart->buadrate)) / 64) - 1;
            break;
        case BUADRATE_ASYNC_8BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNC_MODE;
            TXSTAbits.BRGH = EUSART_ASYNC_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
            baud_rate_Temp = ((_XTAL_FREQ / (float)(_eusart->buadrate)) / 16) - 1;
            break;
        case BUADRATE_ASYNC_16BIT_LOW_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNC_MODE;
            TXSTAbits.BRGH = EUSART_ASYNC_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            baud_rate_Temp = ((_XTAL_FREQ / (float)(_eusart->buadrate)) / 16) - 1;
            break;
        case BUADRATE_ASYNC_16BIT_HIGH_SPEED:
            TXSTAbits.SYNC = EUSART_ASYNC_MODE;
            TXSTAbits.BRGH = EUSART_ASYNC_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            baud_rate_Temp = ((_XTAL_FREQ / (float)(_eusart->buadrate)) / 4) - 1;
            break;
        case BUADRATE_SYNC_8BIT:
            TXSTAbits.SYNC = EUSART_SYNC_MODE;
            //TXSTAbits.BRGH = EUSART_ASYNC_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_8BIT_BAUDRATE_GEN;
            baud_rate_Temp = ((_XTAL_FREQ / (float)(_eusart->buadrate)) / 4) - 1;
            break;    
        case BUADRATE_SYNC_16BIT:
            TXSTAbits.SYNC = EUSART_SYNC_MODE;
            //TXSTAbits.BRGH = EUSART_ASYNC_LOW_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            baud_rate_Temp = ((_XTAL_FREQ / (float)(_eusart->buadrate)) / 4) - 1;
            break; 
        default:
            TXSTAbits.SYNC = EUSART_ASYNC_MODE;
            TXSTAbits.BRGH = EUSART_ASYNC_HIGH_SPEED;
            BAUDCONbits.BRG16 = EUSART_16BIT_BAUDRATE_GEN;
            break;
    }
    
    SPBRG = (uint8)((uint32)baud_rate_Temp); 
    SPBRGH = (uint8)((uint32)baud_rate_Temp >> 8);
}

static void eusart_async_tx_init(const usart_t *_eusart){
    if(_eusart->usart_tx_cfg.usart_tx_enable == EUSART_ASYNC_TX_ENABLE){
        TXSTAbits.TXEN = EUSART_ASYNC_TX_ENABLE;
        EUSART_TX_InterruptHandler = _eusart->EUSART_TX_DefaultInterruptHandler;
        /*EUSART Transmit interrupt*/
        if(_eusart->usart_tx_cfg.usart_tx_interrupt_enable == EUSART_ASYNC_INTERRUPT_TX_ENABLE){
            PIE1bits.TXIE = EUSART_ASYNC_INTERRUPT_TX_ENABLE;
            
            
            #if EUSART_TX_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
            EUSART_TX_Interrupt_Enable();
            
            #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
            Interrupt_PriorityLevelsEnable();
            if(_eusart->usart_tx_cfg.usart_tx_priority == INTERRUPT_High_Priority){
                Interrupt_GlobalInterruptHighEnable();
                EUSART_TX_Interrupt_Priority_High();
            }
            else{
                Interrupt_GlobalInterruptLowEnable();
                EUSART_TX_Interrupt_Priority_Low();
            }
            #else
            /*Enable Global Interrupt */
            Interrupt_GlobalInterruptEnable();
            /*Enable Peripherals Interrupt */
            Interrupt_PeripheralInterruptEnable();
            
            #endif
            
            #endif
        }else{
            PIE1bits.TXIE = EUSART_ASYNC_INTERRUPT_TX_DISABLE;
        }
        /*EUSART Transmit 9BIT CONFG*/
        if(_eusart->usart_tx_cfg.usart_tx_9bit_enable == EUSART_ASYNC_9BIT_TX_ENABLE){
            TXSTAbits.TX9 = EUSART_ASYNC_9BIT_TX_ENABLE;
        }else{
            TXSTAbits.TX9 = EUSART_ASYNC_9BIT_TX_DISABLE;
        }
        
        /**/
    }
    
    else{ /* Nothing */ }
    
}

static void eusart_async_rx_init(const usart_t *_eusart){
    
    if(_eusart->usart_rx_cfg.usart_rx_enable == EUSART_ASYNC_RX_ENABLE){
        
        RCSTAbits.CREN = EUSART_ASYNC_RX_ENABLE;
        
        EUSART_RX_InterruptHandler = _eusart->EUSART_RX_DefaultInterruptHandler;
        EUSART_FramingErrorHandler = _eusart->EUSART_FramingErrorHandler;
        EUSART_OverrunErrorHandler = _eusart->EUSART_OverrunErrorHandler;
        /*EUSART Transmit interrupt*/
        if(_eusart->usart_rx_cfg.usart_rx_interrupt_enable == EUSART_ASYNC_INTERRUPT_RX_ENABLE){
            PIE1bits.RCIE = EUSART_ASYNC_INTERRUPT_RX_ENABLE;
            
            #if EUSART_RX_INTERRUPT_FEATURE_ENABLE == Interrupt_Feature_Enable
            EUSART_RX_Interrupt_Enable();
            
            #if Interrupt_Priority_Levels_Enable == Interrupt_Feature_Enable
            Interrupt_PriorityLevelsEnable();
            if(_eusart->usart_rx_cfg.usart_rx_priority == INTERRUPT_High_Priority){
                Interrupt_GlobalInterruptHighEnable();
                EUSART_RX_Interrupt_Priority_High();
            }
            else{
                Interrupt_GlobalInterruptLowEnable();
                EUSART_RX_Interrupt_Priority_Low();
            }
            #else
            /*Enable Global Interrupt */
            Interrupt_GlobalInterruptEnable();
            /*Enable Peripherals Interrupt */
            Interrupt_PeripheralInterruptEnable();
            
            #endif
            
            #endif
            
        }else{
            PIE1bits.RCIE = EUSART_ASYNC_INTERRUPT_RX_DISABLE;
        }

        /*EUSART Transmit 9BIT CONFG*/
        if(_eusart->usart_rx_cfg.usart_rx_9bit_enable == EUSART_ASYNC_9BIT_RX_ENABLE){
            RCSTAbits.RC9 = EUSART_ASYNC_9BIT_RX_ENABLE;
        }else{
            RCSTAbits.RC9 = EUSART_ASYNC_9BIT_RX_DISABLE;
        }
    }
    
    else {/* Nothing */}
}



void EUSART_TX_ISR(void){
    PIE1bits.TXIE = 0;
    if(EUSART_TX_InterruptHandler){
        EUSART_TX_InterruptHandler();
    }
    else{}
    
}
void EUSART_RX_ISR(void){
    if(EUSART_RX_InterruptHandler){
        EUSART_RX_InterruptHandler();
    }
    else{}
    if(EUSART_FramingErrorHandler){
        EUSART_FramingErrorHandler();
    }
    else{}
    if(EUSART_OverrunErrorHandler){
        EUSART_OverrunErrorHandler();
    }
    else{}
}