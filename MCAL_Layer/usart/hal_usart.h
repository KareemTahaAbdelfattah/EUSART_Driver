/* 
 * File:   hal_usart.h
 * Author: Kareem Taha
 *
 * Created on Feb 20, 2023, 8:49 PM
 */


#ifndef HAL_USART_H
#define	HAL_USART_H

 /* Section : Includes */

#include "../std_types.h"
#include "pic18f4620.h"
#include "../device_config.h"
#include "../hal_gpio.h"
#include "hal_usart_cfg.h"
#include "../Interrupt/hal_internal_interrupt.h"

 /* Section : Macros Definition */
#define EUSART_ENABLE                       1
#define EUSART_DISABLE                      0


#define EUSART_SYNC_MODE                    1
#define EUSART_ASYNC_MODE                   0

#define EUSART_ASYNC_HIGH_SPEED             1
#define EUSART_ASYNC_LOW_SPEED              0


#define EUSART_16BIT_BAUDRATE_GEN           1
#define EUSART_8BIT_BAUDRATE_GEN            0



//TX
#define EUSART_ASYNC_TX_ENABLE             1
#define EUSART_ASYNC_TX_DISABLE            0

#define EUSART_ASYNC_INTERRUPT_TX_ENABLE             1
#define EUSART_ASYNC_INTERRUPT_TX_DISABLE            0  

#define EUSART_ASYNC_9BIT_TX_ENABLE             1
#define EUSART_ASYNC_9BIT_TX_DISABLE            0


//RX
#define EUSART_ASYNC_RX_ENABLE             1
#define EUSART_ASYNC_RX_DISABLE            0

#define EUSART_ASYNC_INTERRUPT_RX_ENABLE             1
#define EUSART_ASYNC_INTERRUPT_RX_DISABLE            0  

#define EUSART_ASYNC_9BIT_RX_ENABLE             1
#define EUSART_ASYNC_9BIT_RX_DISABLE            0

//ERROR
#define EUSART_FRAMING_ERROR_DETECTED           1
#define EUSART_FRAMING_ERROR_CLEARED            0

#define EUSART_OVERRUN_ERROR_DETECTED           1
#define EUSART_OVERRUN_ERROR_CLEARED            0


 /* Section : Macros Functions Declaration */

 /* Section : Data Types Declaration */

typedef enum{
    BUADRATE_ASYNC_8BIT_LOW_SPEED,
    BUADRATE_ASYNC_8BIT_HIGH_SPEED,
    BUADRATE_ASYNC_16BIT_LOW_SPEED,
    BUADRATE_ASYNC_16BIT_HIGH_SPEED,
    BUADRATE_SYNC_8BIT,
    BUADRATE_SYNC_16BIT
}buadrate_gen_t;


typedef struct{
    uint8 usart_tx_reserved : 5;
    uint8 usart_tx_enable: 1;
    uint8 usart_tx_interrupt_enable: 1;
    uint8 usart_tx_9bit_enable: 1;
    Interrupt_Priority_cfg usart_tx_priority;
}usart_tx_cfg_t;

typedef struct{
    uint8 usart_rx_reserved : 5;
    uint8 usart_rx_enable: 1;
    uint8 usart_rx_interrupt_enable: 1;
    uint8 usart_rx_9bit_enable: 1;
    Interrupt_Priority_cfg usart_rx_priority;
}usart_rx_cfg_t;

typedef union{
    struct{
        uint8 usart_tx_reserved:5;
        uint8 usart_ferr:5;
        uint8 usart_oerr:5;
    };
    uint8 status;
}usart_status_error_t;



typedef struct{
    uint32 buadrate;
    buadrate_gen_t buadrate_gen_cfg;
    usart_tx_cfg_t usart_tx_cfg;
    usart_rx_cfg_t usart_rx_cfg;
    usart_status_error_t usart_error;
    void(*EUSART_TX_DefaultInterruptHandler)(void);
    void(*EUSART_RX_DefaultInterruptHandler)(void);
    void(*EUSART_FramingErrorHandler)(void);
    void(*EUSART_OverrunErrorHandler)(void);
}usart_t;



 /* Section : Function Declaration */

STD_ReturnType EUSART_ASYNC_Init(const usart_t *_eusart);
STD_ReturnType EUSART_ASYNC_DeInit(const usart_t *_eusart);
STD_ReturnType EUSART_ASYNC_ReadByte_Blocking(const usart_t *_eusart, uint8 *_data);
STD_ReturnType EUSART_ASYNC_ReadByte_NonBlocking(const usart_t *_eusart, uint8 *_data);
STD_ReturnType EUSART_ASYNC_WriteByte_Blocking(const usart_t *_eusart, uint8 _data);
STD_ReturnType EUSART_ASYNC_WriteString_Blocking(const usart_t *_eusart, uint8 *_data, uint32 str_len);

#endif	/* HAL_USART_H */

