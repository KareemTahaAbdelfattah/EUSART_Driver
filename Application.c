/* 
 * File:   Application.c
 * Author: Kareem Taha Abdelfatah Mohammed
 * https://www.linkedin.com/in/kareem-taha-ba451621a/
 * Created on September 13, 2022, 9:10 PM
 */

#include "Application.h"

STD_ReturnType ret = E_OK;

/*
ch_lcd_4bit_t lcd_1 = {
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN0,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_rs.direction = GPIO_OUTPUT_DIRECTION,
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN1,
  .lcd_en.logic = GPIO_LOW,
  .lcd_en.direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_4_bit[0].port = PORTC_INDEX,
  .lcd_data_4_bit[0].pin = GPIO_PIN2,
  .lcd_data_4_bit[0].logic = GPIO_LOW,
  .lcd_data_4_bit[0].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_4_bit[1].port = PORTC_INDEX,
  .lcd_data_4_bit[1].pin = GPIO_PIN3,
  .lcd_data_4_bit[1].logic = GPIO_LOW,
  .lcd_data_4_bit[1].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_4_bit[2].port = PORTC_INDEX,
  .lcd_data_4_bit[2].pin = GPIO_PIN4,
  .lcd_data_4_bit[2].logic = GPIO_LOW,
  .lcd_data_4_bit[2].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_4_bit[3].port = PORTC_INDEX,
  .lcd_data_4_bit[3].pin = GPIO_PIN5,
  .lcd_data_4_bit[3].logic = GPIO_LOW,
  .lcd_data_4_bit[3].direction = GPIO_OUTPUT_DIRECTION
};


ch_lcd_8bit_t lcd_2 = {
  .lcd_rs.port = PORTC_INDEX,
  .lcd_rs.pin = GPIO_PIN6,
  .lcd_rs.logic = GPIO_LOW,
  .lcd_rs.direction = GPIO_OUTPUT_DIRECTION,
  .lcd_en.port = PORTC_INDEX,
  .lcd_en.pin = GPIO_PIN7,
  .lcd_en.logic = GPIO_LOW,
  .lcd_en.direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[0].port = PORTD_INDEX,
  .lcd_data_8_bit[0].pin = GPIO_PIN0,
  .lcd_data_8_bit[0].logic = GPIO_LOW,
  .lcd_data_8_bit[0].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[1].port = PORTD_INDEX,
  .lcd_data_8_bit[1].pin = GPIO_PIN1,
  .lcd_data_8_bit[1].logic = GPIO_LOW,
  .lcd_data_8_bit[1].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[2].port = PORTD_INDEX,
  .lcd_data_8_bit[2].pin = GPIO_PIN2,
  .lcd_data_8_bit[2].logic = GPIO_LOW,
  .lcd_data_8_bit[2].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[3].port = PORTD_INDEX,
  .lcd_data_8_bit[3].pin = GPIO_PIN3,
  .lcd_data_8_bit[3].logic = GPIO_LOW,
  .lcd_data_8_bit[3].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[4].port = PORTD_INDEX,
  .lcd_data_8_bit[4].pin = GPIO_PIN4,
  .lcd_data_8_bit[4].logic = GPIO_LOW,
  .lcd_data_8_bit[4].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[5].port = PORTD_INDEX,
  .lcd_data_8_bit[5].pin = GPIO_PIN5,
  .lcd_data_8_bit[5].logic = GPIO_LOW,
  .lcd_data_8_bit[5].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[6].port = PORTD_INDEX,
  .lcd_data_8_bit[6].pin = GPIO_PIN6,
  .lcd_data_8_bit[6].logic = GPIO_LOW,
  .lcd_data_8_bit[6].direction = GPIO_OUTPUT_DIRECTION,
  .lcd_data_8_bit[7].port = PORTD_INDEX,
  .lcd_data_8_bit[7].pin = GPIO_PIN7,
  .lcd_data_8_bit[7].logic = GPIO_LOW,
  .lcd_data_8_bit[7].direction = GPIO_OUTPUT_DIRECTION
};


keypad_t kaypad_1 = {
    .keypad_row_pins[0].pin = GPIO_PIN0,
    .keypad_row_pins[1].pin = GPIO_PIN1,
    .keypad_row_pins[2].pin = GPIO_PIN2,
    .keypad_row_pins[3].pin = GPIO_PIN3,
    .keypad_row_pins[0].port = PORTD_INDEX,
    .keypad_row_pins[1].port = PORTD_INDEX,
    .keypad_row_pins[2].port = PORTD_INDEX,
    .keypad_row_pins[3].port = PORTD_INDEX,
    .keypad_row_pins[0].logic = GPIO_LOW,
    .keypad_row_pins[1].logic = GPIO_LOW,
    .keypad_row_pins[2].logic = GPIO_LOW,
    .keypad_row_pins[3].logic = GPIO_LOW,
    .keypad_row_pins[0].direction = GPIO_OUTPUT_DIRECTION,
    .keypad_row_pins[1].direction = GPIO_OUTPUT_DIRECTION,
    .keypad_row_pins[2].direction = GPIO_OUTPUT_DIRECTION,
    .keypad_row_pins[3].direction = GPIO_OUTPUT_DIRECTION,
    .keypad_colomns_pins[0].pin = GPIO_PIN4,
    .keypad_colomns_pins[1].pin = GPIO_PIN5,
    .keypad_colomns_pins[2].pin = GPIO_PIN6,
    .keypad_colomns_pins[3].pin = GPIO_PIN7,
    .keypad_colomns_pins[0].port = PORTD_INDEX,
    .keypad_colomns_pins[1].port = PORTD_INDEX,
    .keypad_colomns_pins[2].port = PORTD_INDEX,
    .keypad_colomns_pins[3].port = PORTD_INDEX,
    .keypad_colomns_pins[0].logic = GPIO_LOW,
    .keypad_colomns_pins[1].logic = GPIO_LOW,
    .keypad_colomns_pins[2].logic = GPIO_LOW,
    .keypad_colomns_pins[3].logic = GPIO_LOW,
    .keypad_colomns_pins[0].direction = GPIO_INPUT_DIRECTION,
    .keypad_colomns_pins[1].direction = GPIO_INPUT_DIRECTION,
    .keypad_colomns_pins[2].direction = GPIO_INPUT_DIRECTION,
    .keypad_colomns_pins[3].direction = GPIO_INPUT_DIRECTION,
};

void welcome_massege(void){
    for(int i = 1; i <= 6; i++){
        lcd_4_bit_send_string_pos(&lcd_1, 1, i, "Hello All");
        lcd_4_bit_send_string_pos(&lcd_1, 2, 5, "!Calculator!");
        _delay(250000);
        lcd_4_bit_send_string_pos(&lcd_1, 1, i, " ");
    }
    lcd_4_bit_send_string_pos(&lcd_1, 1, 1, "                  ");
    lcd_4_bit_send_string_pos(&lcd_1, 1, 6, "Hello All");
}

void loading(void){
    lcd_4_bit_send_string_pos(&lcd_1, 1, 1, "Loading");
    for(int i = 8; i <= 15; i++){
        lcd_4_bit_send_char_data_pos(&lcd_1, 1, i, '.');
        _delay(250000);
    }
}*/

/*
led_t led1 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN0,
  .port_name = PORTC_INDEX,
};



led_t led2 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN1,
  .port_name = PORTC_INDEX,
};


led_t led3 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN2,
  .port_name = PORTC_INDEX,
};

led_t led4 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN3,
  .port_name = PORTC_INDEX,
};

void RB_int0_app_isr(void){
   ret = led_toggle_logic(&led1);
}


void RB_int1_app_isr(void){
   ret = led_toggle_logic(&led2);
}

void RB_int2_app_isr(void){
   ret = led_toggle_logic(&led3);
}

void RB_int3_app_isr(void){
   ret = led_toggle_logic(&led4);
}


Interrupt_RBx_t int1_obj = {
   .Interrupt_Handler = RB_int0_app_isr,
   .priority = INTERRUPT_Low_Priority,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN4,
};
Interrupt_RBx_t int2_obj = {
   .Interrupt_Handler = RB_int1_app_isr,
   .priority = INTERRUPT_Low_Priority,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN5,
};
Interrupt_RBx_t int3_obj = {
   .Interrupt_Handler = RB_int2_app_isr,
   .priority = INTERRUPT_Low_Priority,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN6,
};
Interrupt_RBx_t int4_obj = {
   .Interrupt_Handler = RB_int3_app_isr,
   .priority = INTERRUPT_Low_Priority,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN7,
};*/


/*
void int0_app_isr(void){
   ret = led_toggle_logic(&led1);
}


void int1_app_isr(void){
   ret = led_toggle_logic(&led2);
}

void int2_app_isr(void){
   ret = led_toggle_logic(&led3);
}
Interrupt_INTx_t int0_obj = {
   .Interrupt_Handler = int0_app_isr,
   .edge = INTERRUPT_RAISING_EDGE,
   .priority = INTERRUPT_High_Priority,
   .source = INTERRUPT_EXTERNAL_INT0,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN0,
};

Interrupt_INTx_t int1_obj = {
   .Interrupt_Handler = int1_app_isr,
   .edge = INTERRUPT_RAISING_EDGE,
   .priority = INTERRUPT_Low_Priority,
   .source = INTERRUPT_EXTERNAL_INT1,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN1,
};


Interrupt_INTx_t int2_obj = {
   .Interrupt_Handler = int2_app_isr,
   .edge = INTERRUPT_RAISING_EDGE,
   .priority = INTERRUPT_High_Priority,
   .source = INTERRUPT_EXTERNAL_INT2,
   .mcu_pin.direction = GPIO_INPUT_DIRECTION,
   .mcu_pin.port = PORTB_INDEX,
   .mcu_pin.logic = GPIO_LOW,
   .mcu_pin.pin = GPIO_PIN2,
};*/

//uint8 epprom_cnt = 0, value = 0;

/*
pin_config_t pin_1 = {
  .direction = GPIO_OUTPUT_DIRECTION,
  .logic = GPIO_LOW,
  .pin = GPIO_PIN3,
  .port = PORTC_INDEX,
};

led_t led2 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN1,
  .port_name = PORTC_INDEX,
};

led_t led3 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN2,
  .port_name = PORTC_INDEX,
};

volatile uint32 counter_value = 0;

void timer0_defaultHandler(void){
    counter_value++;
    led_toggle_logic(&led1);
    led_toggle_logic(&led2);
    led_toggle_logic(&led3);
};*/


/*
void timer2_defaultHandler(void){
    led_toggle_logic(&led2);
    led_toggle_logic(&led3);
};




timer0_t timer0_obj = {
    .TIMER0_InterruptHandler = timer0_defaultHandler,
    .timer0_mode = TIMER0_SOURCE_TIMER_MOD,
    .timer0_reg_size = TIMER0_16_BIT,
    .prescaler_en = TIMER0_PRESCLAER_ENABLE_CFG,
    .prescaler_value = TIMER0_PRESCALER_DIV_BY_16,
    .timer0_preload_value = 3036
};

void timer1_defaultHandler(void){

};

timer1_t timer1_obj = {
    .TIMER1_InterruptHandler = timer1_defaultHandler,
    .timer1_mode = TIMER1_SOURCE_TIMER_MOD,
    .priority = INTERRUPT_Low_Priority,
    .timer1_preload_value = 3036,
    .timer1_prescaler = TIMER1_PRESCALER_DIV_BY_8,
    .timer1_reg_rw_mode = TIMER1_RW_REG_MODE_16BIT,
};





timer1_t counter1_obj = {
    .TIMER1_InterruptHandler = NULL,
    .timer1_mode = TIMER1_SOURCE_COUNTER_MOD,
    .timer1_preload_value = 0,
    .timer1_prescaler = TIMER1_PRESCALER_DIV_BY_1,
    .timer1_reg_rw_mode = TIMER1_RW_REG_MODE_16BIT,
    .timer1_counter_mode = TIMER1_ASYNC_COUNTER_MOD,
};



timer2_t timer2_obj = {
  .TIMER2_InterruptHandler = NULL,
  .timer2_postscaler = TIMER2_POSTSCALER_DIV_BY_1,
  .timer2_prescaler = TIMER2_PRESCALER_DIV_BY_1,
  .timer2_preload_value = 0,
};*/

/*
ccp_t ccp1_obj = {
  .CCP1_InterruptHandler =  NULL,
  .PWM_Frequency = 20000,
  .ccp_mode = CCP_PWM_MODE_,
  .ccp_inst = CCP1_INST,
  .pin_ccp.direction = GPIO_OUTPUT_DIRECTION,
  .pin_ccp.pin = GPIO_PIN2,
  .pin_ccp.port = PORTC_INDEX,
  .timer2_postscaler = CCP_TIMER2_POSTSCALER_DIV_BY_1,
  .timer2_prescaler = CCP_TIMER2_PRESCALER_DIV_BY_1,
};


ccp_t ccp2_obj = {
  .CCP2_InterruptHandler =  NULL,
  .PWM_Frequency = 20000,
  .ccp_mode = CCP_PWM_MODE_,
  .ccp_inst = CCP2_INST,
  .pin_ccp.direction = GPIO_OUTPUT_DIRECTION,
  .pin_ccp.pin = GPIO_PIN1,
  .pin_ccp.port = PORTC_INDEX,
  .timer2_postscaler = CCP_TIMER2_POSTSCALER_DIV_BY_1,
  .timer2_prescaler = CCP_TIMER2_PRESCALER_DIV_BY_1,
};*/

/*
uint16 v_digital = 0;


adc_conf_t adc_obj = {
  .ADC_InterruptHandler = NULL,
  .acquicition_time = ADC_8_TAD,
  .format_status = ADC_RESULT_RIGHT,
  .onversion_clock = ADC_CONVERSION_CLOCK_FOSC_DIV_16,
  .select_channel = ADC_CHANNEL_AN0,
  .voltage_ref = ADC_VOLTAGE_REF_DISABLE,
};



void timer3_defaultHandler(void){
};

timer3_t timer3_obj = {
    .TIMER3_InterruptHandler = NULL,
    .timer3_mode = TIMER3_SOURCE_TIMER_MOD,
    .timer3_preload_value = 0,
    .timer3_prescaler = TIMER3_PRESCALER_DIV_BY_1,
    .timer3_reg_rw_mode = TIMER3_RW_REG_MODE_16BIT,
};

ccp_t ccp1_obj;

void ccp1_defaultHandler(void){
    timer3_write_value(&timer3_obj, 0);
};

ccp_t ccp1_obj = {
  .CCP1_InterruptHandler =  ccp1_defaultHandler,
  .ccp_mode = CCP_COMPARE_MODE,
  .ccp_mode_varient = CCP_COMPARE_MODE_TOGGLE_ON_MATCH,
  .ccp_inst = CCP1_INST,
  .pin_ccp.direction = GPIO_OUTPUT_DIRECTION,
  .pin_ccp.pin = GPIO_PIN2,
  .pin_ccp.port = PORTC_INDEX,
  .ccp_capture_timer = CCP1_CCP2_TIMER3,
};*/

uint8 value_usart;

led_t led1 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN7,
  .port_name = PORTB_INDEX,
};


led_t led2 = {
  .led_status = LED_LOW,
  .pin_number = GPIO_PIN0,
  .port_name = PORTB_INDEX,
};

void EUSART_IN(void){
    led_toggle_logic(&led1);
}

void EUSART_OUT(void);

usart_t usart_obj = {
    .buadrate = 9600,
    .buadrate_gen_cfg = BUADRATE_ASYNC_8BIT_LOW_SPEED,
    .usart_rx_cfg.usart_rx_9bit_enable = EUSART_ASYNC_9BIT_RX_DISABLE,
    .usart_rx_cfg.usart_rx_enable = EUSART_ASYNC_RX_ENABLE,
    .usart_rx_cfg.usart_rx_interrupt_enable = EUSART_ASYNC_INTERRUPT_RX_ENABLE,
    .usart_tx_cfg.usart_tx_9bit_enable = EUSART_ASYNC_9BIT_TX_DISABLE,
    .usart_tx_cfg.usart_tx_enable = EUSART_ASYNC_TX_ENABLE,
    .usart_tx_cfg.usart_tx_interrupt_enable = EUSART_ASYNC_INTERRUPT_TX_ENABLE,
    .EUSART_FramingErrorHandler = NULL,
    .EUSART_OverrunErrorHandler = NULL,
    .EUSART_RX_DefaultInterruptHandler = EUSART_OUT,
    .EUSART_TX_DefaultInterruptHandler = EUSART_IN,
};

void EUSART_OUT(void){
    led_toggle_logic(&led2);
    ret = EUSART_ASYNC_ReadByte_NonBlocking(&usart_obj, &value_usart);
    switch(value_usart){
        case 'a':
            led_turn_on(&led1);
            led_turn_on(&led2);
            break;
        default:
            break;
    }
    /*Clear flag when reading register buffer*/
}

   

int main() { 
    Application_initialize();
    //ret = ADC_Init(&adc_obj);
    //ret = ADC_Start_Conversion(&adc_obj);
    //ret = timer3_init(&timer3_obj);
    //ret = CCP_CompareMode_set_Value(&ccp1_obj, 50000);
    //ret = CCP_Init(&ccp1_obj);
    //ret = CCP_PWM_Set_Duty(&ccp2_obj, 100);
    //ret = CCP_PWM_Start(&ccp2_obj); 
    while(1){
        
        
        //EUSART_ASYNC_WriteString_Blocking(&usart_obj, "Hello\r", 6);
        
        
//        EUSART_ASYNC_WriteByte_Blocking(&usart_obj, 'a');
//        __delay_ms(1000);
//        EUSART_ASYNC_WriteByte_Blocking(&usart_obj, 'b');
//        __delay_ms(1000);
       
        
        /*EUSART_ASYNC_WriteString_Blocking(&usart_obj, "Kareem\r", 7);
        __delay_ms(500);
        EUSART_ASYNC_WriteString_Blocking(&usart_obj, "Taha\r", 5);
        __delay_ms(500);*/
        

//        ret = EUSART_ASYNC_ReadByte_NonBlocking(&usart_obj, &value_usart);
//        if('a' == value_usart){
//            led_turn_on(&led1);
//            EUSART_ASYNC_WriteString_Blocking(&usart_obj, "LED ON\r", 7);
//        }
//        else if('b' == value_usart){
//            led_turn_off(&led1);
//            EUSART_ASYNC_WriteString_Blocking(&usart_obj, "LED OFF\r", 8);
//        }
    }
    return (EXIT_SUCCESS);
}

/* initialize any pin with direction & logic */
void Application_initialize(void){
    //gpio_pin_direction_init(&pin_1);
    EUSART_ASYNC_Init(&usart_obj);
    led_initialize(&led1);
    led_initialize(&led2);
}
