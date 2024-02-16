/* STM32F407  */
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_rcc.h"

void SystemClock_Config(void) {
    
}

void delay(volatile int d) {
    while (d--) {
        __NOP();
    }
}

int main() {
    // Configure the system clock
    SystemClock_Config();

    // Initialize GPIO for LED D2 (PA6) and LED D3 (PA7)
    GPIO_InitTypeDef GPIO_InitStruct;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Initialize the pins to be off (assuming LEDs are active high)
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);

    while (1) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_9);
        delay(1000000 / 6); // Blink 3 times per second
    }

    return 0;
}
