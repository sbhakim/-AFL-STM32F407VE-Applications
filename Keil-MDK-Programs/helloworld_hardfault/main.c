/* STM32F407  */

#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"
#include <string.h>

void SystemClock_Config(void);

unsigned int etm_tc_len __attribute__((section(".non_init")));
unsigned char etm_tc[2000] __attribute__((section(".non_init")));
unsigned int etm_tc_idx = 0;
unsigned int etm_exit = 0;

void SystemClock_Config(void) {
    /* The SystemClock_Config function is currently not implemented in this code. As a result, 
	    the microcontroller will use its default system clock source, which is the High-Speed Internal (HSI)
	    RC oscillator, operating at a frequency of 16 MHz. */
}

void delay(volatile int d) {
    while (d--) {
        __NOP();
    }
}

int main(void) {
    /* Configure the system clock */
    SystemClock_Config();

    /* Breakpoint before LED Initialization */
    __asm("bkpt 0xEF\n\t");

    /* Initialize GPIO for LED D2 (PA6) and LED D3 (PA7) */
    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Initialize the pins to be off (assuming LEDs are active high) */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);

    /* Breakpoint before LED blinking loop */
    
    while (1) {
        /* Breakpoint before LED toggle */
     

        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
        delay(1000000 / 6); // Blink 3 times per second

        /* Breakpoint after LED toggle */
    }

    /* Breakpoint after LED blinking loop */
    __asm("bkpt 0xFF\n\t");

    return 0;
}
