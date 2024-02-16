/* STM32F407  */

#include "stm32f4xx.h"
#include "stm32f4xx_hal_uart.h"
#include <string.h>

void SystemClock_Config(void);

unsigned int etm_tc_len __attribute__((section(".non_init")));
unsigned char etm_tc[2000] __attribute__((section(".non_init")));

void SystemClock_Config(void) {
   /* The SystemClock_Config function is currently not implemented in this code. As a result, 
	    the microcontroller will use its default system clock source, which is the High-Speed Internal (HSI)
	    RC oscillator, operating at a frequency of 16 MHz. */
}

int main(void) {
    /* Configure the system clock */
    SystemClock_Config();

    /* Enable GPIO clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /* Enable USART2 clock */
    __HAL_RCC_USART2_CLK_ENABLE();

    /* 
	  /* This section initializes the GPIO pins PA2 and PA3 for UART functionality. The pins 
	    are configured for alternate function push-pull mode, with a pull-up resistor and very high speed. 
    	This setup is necessary  for the USART2 peripheral to use these pins for transmitting and receiving data. */

	 
    GPIO_InitTypeDef  GPIO_InitStruct;
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;  // USART2 Alternate function
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* Initialize and configure the UART peripheral */
    UART_HandleTypeDef UartHandle;

    UartHandle.Instance = USART2;
    UartHandle.Init.BaudRate = 115200;
    UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
    UartHandle.Init.StopBits = UART_STOPBITS_1;
    UartHandle.Init.Parity = UART_PARITY_NONE;
    UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartHandle.Init.Mode = UART_MODE_TX_RX;

    if (HAL_UART_Init(&UartHandle) != HAL_OK) {
        /* Initialization Error */
        while (1);
    }

    /* Breakpoint before sending data */
    __asm("bkpt 0xEF\n\t");

    /* Send data through UART */
    if(HAL_UART_Transmit(&UartHandle, etm_tc, etm_tc_len, 5000) != HAL_OK)
			/* Here 5000 is a timeout value */
    {
        /* Transfer error in transmission process */
        while(1);
    }

    /* Breakpoint after sending data */
    __asm("bkpt 0xFF\n\t");

    /* Commented loop for echoing received characters back */
    uint8_t ch;
    while (1)
    {
        HAL_UART_Receive(&UartHandle, &ch, 1, 5000);
        HAL_UART_Transmit(&UartHandle, &ch, 1, 5000);
    }
    
    
    return 0;
}
