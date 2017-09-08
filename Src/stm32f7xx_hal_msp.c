/**
  ******************************************************************************
  * File Name          : stm32f7xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
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
#include "stm32f7xx_hal.h"

extern void _Error_Handler(char *, int);
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* System interrupt init*/
  /* MemoryManagement_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
  /* BusFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
  /* UsageFault_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);
  /* SVCall_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SVCall_IRQn, 0, 0);
  /* DebugMonitor_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DebugMonitor_IRQn, 0, 0);
  /* PendSV_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(PendSV_IRQn, 0, 0);
  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}


void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{

   GPIO_InitTypeDef GPIO_InitStruct;
   if (hltdc->Instance == LTDC)
   {
      /* USER CODE BEGIN LTDC_MspInit 0 */

      /* USER CODE END LTDC_MspInit 0 */
      /* Peripheral clock enable */
      __HAL_RCC_LTDC_CLK_ENABLE();

      /**LTDC GPIO Configuration    
      PB8     ------> LTDC_B6
      PB9     ------> LTDC_B7
      PG11     ------> LTDC_B3
      PA12     ------> LTDC_R5
      PI4     ------> LTDC_B4
      PK7     ------> LTDC_DE
      PG10     ------> LTDC_G3
      PD3     ------> LTDC_G7
      PA11     ------> LTDC_R4
      PI5     ------> LTDC_B5
      PI10     ------> LTDC_HSYNC
      PH15     ------> LTDC_G4
      PI1     ------> LTDC_G6
      PI9     ------> LTDC_VSYNC
      PH13     ------> LTDC_G2
      PI0     ------> LTDC_G5
      PA8     ------> LTDC_R6
      PI14     ------> LTDC_CLK
      PG6     ------> LTDC_R7
      PH9     ------> LTDC_R3 
      */
      GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
      HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

      GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_6;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
      HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

      GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_8;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_10|GPIO_PIN_1 
        |GPIO_PIN_9|GPIO_PIN_0|GPIO_PIN_14;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
      HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

      GPIO_InitStruct.Pin = GPIO_PIN_7;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
      HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

      GPIO_InitStruct.Pin = GPIO_PIN_10;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF9_LTDC;
      HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

      GPIO_InitStruct.Pin = GPIO_PIN_3;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
      HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

      GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_13|GPIO_PIN_9;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_NOPULL;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
      GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
      HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

      /* USER CODE BEGIN LTDC_MspInit 1 */

      /* USER CODE END LTDC_MspInit 1 */
      }

}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc)
{
   if(hltdc->Instance==LTDC)
   {
      /* Peripheral clock disable */
      __HAL_RCC_LTDC_CLK_DISABLE();

      /**LTDC GPIO Configuration    
      PB8     ------> LTDC_B6
      PB9     ------> LTDC_B7
      PG11     ------> LTDC_B3
      PA12     ------> LTDC_R5
      PI4     ------> LTDC_B4
      PK7     ------> LTDC_DE
      PG10     ------> LTDC_G3
      PD3     ------> LTDC_G7
      PA11     ------> LTDC_R4
      PI5     ------> LTDC_B5
      PI10     ------> LTDC_HSYNC
      PH15     ------> LTDC_G4
      PI1     ------> LTDC_G6
      PI9     ------> LTDC_VSYNC
      PH13     ------> LTDC_G2
      PI0     ------> LTDC_G5
      PA8     ------> LTDC_R6
      PI14     ------> LTDC_CLK
      PG6     ------> LTDC_R7
      PH9     ------> LTDC_R3 
      */
      HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8 | GPIO_PIN_9);
      HAL_GPIO_DeInit(GPIOG, GPIO_PIN_11 | GPIO_PIN_10 | GPIO_PIN_6);
      HAL_GPIO_DeInit(GPIOA, GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_8);

      HAL_GPIO_DeInit(GPIOI, GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_10 | GPIO_PIN_1 |
                             GPIO_PIN_9 | GPIO_PIN_0 | GPIO_PIN_14);
      HAL_GPIO_DeInit(GPIOK, GPIO_PIN_7);
      HAL_GPIO_DeInit(GPIOD, GPIO_PIN_3);
      HAL_GPIO_DeInit(GPIOH, GPIO_PIN_15 | GPIO_PIN_13 | GPIO_PIN_9);
   }
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
{
   if(htim_base->Instance==TIM6)
   {
      /* Peripheral clock enable */
      __HAL_RCC_TIM6_CLK_ENABLE();
   }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
{
   if(htim_base->Instance==TIM6)
   {
      /* Peripheral clock disable */
      __HAL_RCC_TIM6_CLK_DISABLE();
   }
}

void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{

   GPIO_InitTypeDef GPIO_InitStruct;
   if (huart->Instance == USART6)
   {
      /* Peripheral clock enable */
      __HAL_RCC_USART6_CLK_ENABLE();

      /**USART6 GPIO Configuration    
      PC6     ------> USART6_TX
      PC7     ------> USART6_RX 
      */
      GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
      GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
      GPIO_InitStruct.Pull = GPIO_PULLUP;
      GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
      GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
      HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
   if(huart->Instance==USART6)
   {
      /* Peripheral clock disable */
      __HAL_RCC_USART6_CLK_DISABLE();

      /**USART6 GPIO Configuration    
      PC6     ------> USART6_TX
      PC7     ------> USART6_RX 
      */
      HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6 | GPIO_PIN_7);
   }
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
