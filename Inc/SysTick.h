#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>

#define SYSTICK_BASEADDRESS       0xE000E010

#define  F_CPU			130000000

typedef struct 
{
    
    volatile uint32_t CSR ;
    volatile uint32_t RVR ;
    volatile uint32_t CVR ;
    volatile uint32_t CALIB ;


}SysTick_t;



#define SysTick    ((SysTick_t*)SYSTICK_BASEADDRESS)


uint8_t SysTick_delay_ms(uint16_t Milli_Seconds);


uint8_t SysTick_delay_us(uint16_t Micro_Seconds);

#endif
