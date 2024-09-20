
#include "SysTick.h"
#include "Cotrex_M4_Reg.h"



#ifndef F_CPU
#error "F_CPU is not defined. Define it in SysTick.h as #define F_CPU value"
#endif


#define SYS_TICK_CLKSOURCE_AHB_DIV8 (1 << 2)  /*==>SysTick clock source (AHB/8)<==*/
#define SYS_TICK_ENABLE             (1 << 0)  /*==>SysTick enable bit<==*/
#define SYS_TICK_COUNTFLAG          (1 << 16) /*==>SysTick count flag<==*/

#define SYS_TICK_MAX_TICKS           0xFFFFFF  // Maximum value for 24-bit SysTick reload register

uint8_t SysTick_delay_ms(uint16_t ms) {
	    /*Assuming F_CPU is 80MHz, but SysTick is running at F_CPU / 8 (10 MHz)*/
	    uint32_t ticks_per_ms = (F_CPU / 8) / 1000;  // Calculate ticks per millisecond
	    uint32_t total_ticks = ticks_per_ms * ms;

	    /*Ensure SysTick is fully disabled before configuring*/
	    SysTick->CSR = 0;  // Disable SysTick to avoid conflicts

	    /*Check if delay exceeds the maximum reload value of SysTick*/
	    while (total_ticks > SYS_TICK_MAX_TICKS) {


	    	/*Load max value into SysTick (subtract 1 as it's zero-indexed)*/
	        SysTick->RVR = SYS_TICK_MAX_TICKS - 1;
	        /*Clear current value register*/
	        SysTick->CVR = 0;
	        /*Enable SysTick timer*/
	        SysTick->CSR = SYS_TICK_CLKSOURCE_AHB_DIV8 | SYS_TICK_ENABLE;

	         /* Wait for the COUNTFLAG to be set (indicating timer has finished)*/
	        while ((SysTick->CSR & SYS_TICK_COUNTFLAG) == 0);

	        /* Subtract the max ticks from total ticks*/

	        total_ticks -= SYS_TICK_MAX_TICKS;
	    }

	    /*Handle the remaining ticks that fit within the SysTick range*/
	    if (total_ticks > 0) {
	        SysTick->RVR = total_ticks - 1;  // Load the remaining ticks
	        SysTick->CVR = 0;                // Clear current value register
	        SysTick->CSR = SYS_TICK_CLKSOURCE_AHB_DIV8 | SYS_TICK_ENABLE;  // Enable SysTick timer

	        /*Wait for the COUNTFLAG to be set*/
	        while ((SysTick->CSR & SYS_TICK_COUNTFLAG) == 0);
	    }
	    /*Disable SysTick after the delay*/
	    SysTick->CSR = 0;
	    return 0;  /*Success*/
}



uint8_t SysTick_delay_us(uint16_t us) {
    uint32_t ticks = (F_CPU / 8 / 1000000) * us;  // Calculate ticks for us delay

    SysTick->RVR = ticks - 1;  // Load the reload value (tick count)
    SysTick->CVR = 0;          // Clear current value register
    SysTick->CSR = SYS_TICK_CLKSOURCE_AHB_DIV8 | SYS_TICK_ENABLE;  // Enable SysTick timer

    // Wait for the COUNTFLAG to be set (indicating timer has finished)
    while ((SysTick->CSR & SYS_TICK_COUNTFLAG) == 0);

    SysTick->CSR = 0;  // Disable SysTick after the delay
    return 0;  // Success

}










