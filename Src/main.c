/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f7xx_hal.h"

// global variable
TIM_HandleTypeDef htim6;
UART_HandleTypeDef huart6;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_TIM6_Init(void);

int main(void)
{
   GPIO_InitTypeDef GPIO_InitStruct;

   HAL_Init();
   SystemClock_Config();

   MX_GPIO_Init();

   MX_USART6_UART_Init();
   MX_TIM6_Init();


   /*Configure GPIO pin : PI1, D1 */
   GPIO_InitStruct.Pin                                   = GPIO_PIN_0;
   GPIO_InitStruct.Mode                                  = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull                                  = GPIO_NOPULL;
   GPIO_InitStruct.Speed                                 = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   /*Configure GPIO pin : PI1, D1 */
   GPIO_InitStruct.Pin                                   = GPIO_PIN_1;
   GPIO_InitStruct.Mode                                  = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull                                  = GPIO_NOPULL;
   GPIO_InitStruct.Speed                                 = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

   if (HAL_UART_Transmit(&huart6, "Hellow World !!!", sizeof("Hellow World !!!"), 1000) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   while (1)
   {
      HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, 0);
      HAL_Delay(500);
      HAL_GPIO_WritePin(GPIOI, GPIO_PIN_1, 1);
      HAL_Delay(500);
   }
}


void HAL_SYSTICK_Callback(void)
{
   if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)
   {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
   }
   else
   {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
   }
}



/** System Clock Configuration
*/
void SystemClock_Config(void)
{
   RCC_OscInitTypeDef RCC_OscInitStruct;
   RCC_ClkInitTypeDef RCC_ClkInitStruct;
   RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

   /**Configure the main internal regulator output voltage 
   */
   __HAL_RCC_PWR_CLK_ENABLE();
   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

   /**Initializes the CPU, AHB and APB busses clocks 
   */
   RCC_OscInitStruct.OscillatorType                      = RCC_OSCILLATORTYPE_HSI;
   RCC_OscInitStruct.HSIState                            = RCC_HSI_ON;
   RCC_OscInitStruct.HSICalibrationValue                 = 16;
   RCC_OscInitStruct.PLL.PLLState                        = RCC_PLL_NONE;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   /**Initializes the CPU, AHB and APB busses clocks 
   */
   RCC_ClkInitStruct.ClockType                           = RCC_CLOCKTYPE_HCLK       |
                                                           RCC_CLOCKTYPE_SYSCLK     |
                                                           RCC_CLOCKTYPE_PCLK1      |
                                                           RCC_CLOCKTYPE_PCLK2;
   RCC_ClkInitStruct.SYSCLKSource                        = RCC_SYSCLKSOURCE_HSI;
   RCC_ClkInitStruct.AHBCLKDivider                       = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider                      = RCC_HCLK_DIV1;
   RCC_ClkInitStruct.APB2CLKDivider                      = RCC_HCLK_DIV1;

   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART6;
   PeriphClkInitStruct.Usart6ClockSelection = RCC_USART6CLKSOURCE_PCLK2;
   if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   /**Configure the Systick interrupt time 
   */
   HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

   /**Configure the Systick 
   */
   HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

   /* SysTick_IRQn interrupt configuration */
   HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
static void MX_GPIO_Init(void)
{
   /* GPIO Ports Clock Enable */
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOH_CLK_ENABLE();
   __HAL_RCC_GPIOI_CLK_ENABLE();
}

/* TIM6 init function */
static void MX_TIM6_Init(void)
{
   TIM_MasterConfigTypeDef sMasterConfig;

   htim6.Instance                                        = TIM6;
   htim6.Init.Prescaler                                  = 0;
   htim6.Init.CounterMode                                = TIM_COUNTERMODE_UP;
   htim6.Init.Period                                     = 0;
   htim6.Init.AutoReloadPreload                          = TIM_AUTORELOAD_PRELOAD_DISABLE;
   if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   sMasterConfig.MasterOutputTrigger                     = TIM_TRGO_RESET;
   sMasterConfig.MasterSlaveMode                         = TIM_MASTERSLAVEMODE_DISABLE;
   if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

}

static void MX_USART6_UART_Init(void)
{
   huart6.Instance                                       = USART6;
   huart6.Init.BaudRate                                  = 115200;
   huart6.Init.WordLength                                = UART_WORDLENGTH_8B;
   huart6.Init.StopBits                                  = UART_STOPBITS_1;
   huart6.Init.Parity                                    = UART_PARITY_NONE;
   huart6.Init.Mode                                      = UART_MODE_TX_RX;
   huart6.Init.HwFlowCtl                                 = UART_HWCONTROL_NONE;
   huart6.Init.OverSampling                              = UART_OVERSAMPLING_16;
   huart6.Init.OneBitSampling                            = UART_ONE_BIT_SAMPLE_DISABLE;
   huart6.AdvancedInit.AdvFeatureInit                    = UART_ADVFEATURE_NO_INIT;
   if (HAL_UART_Init(&huart6) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
   /* USER CODE BEGIN Error_Handler_Debug */
   /* User can add his own implementation to report the HAL error return state */
   while(1) 
   {
   }
   /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
   /* USER CODE BEGIN 6 */
   /* User can add his own implementation to report the file name and line number,
   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
   /* USER CODE END 6 */

}

#endif

