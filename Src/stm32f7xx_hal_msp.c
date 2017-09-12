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


/* --------------------------------------------------------------------------
 * Name : HAL_MspInit()
 *        Initializes the Global MSP.
 *
 * -------------------------------------------------------------------------- */
void HAL_MspInit(void)
{
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
}

/* --------------------------------------------------------------------------
 * Name : HAL_LTDC_MspInit()
 *        
 *
 * -------------------------------------------------------------------------- */
void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{
   GPIO_InitTypeDef gpio_init_structure;
   static RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

   /* Enable the LTDC clocks */
   __HAL_RCC_LTDC_CLK_ENABLE();

   /* LCD clock configuration */
   /* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
   /* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAIN = 429 Mhz */
   /* PLLLCDCLK = PLLSAI_VCO Output/PLLSAIR = 429/5 = 85 Mhz */
   /* LTDC clock frequency = PLLLCDCLK / LTDC_PLLSAI_DIVR_2 = 85/4 = 21 Mhz */
   PeriphClkInitStruct.PeriphClockSelection              = RCC_PERIPHCLK_LTDC;
   PeriphClkInitStruct.PLLSAI.PLLSAIN                    = 192;
   PeriphClkInitStruct.PLLSAI.PLLSAIR                    = 5;
   PeriphClkInitStruct.PLLSAIDivR                        = RCC_PLLSAIDIVR_4;
   HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);   

   /* Enable GPIOs clock */
   __HAL_RCC_GPIOE_CLK_ENABLE();
   __HAL_RCC_GPIOG_CLK_ENABLE();
   __HAL_RCC_GPIOI_CLK_ENABLE();
   __HAL_RCC_GPIOJ_CLK_ENABLE();
   __HAL_RCC_GPIOK_CLK_ENABLE();

   /*** LTDC Pins configuration ***/
   /* GPIOE configuration */
   gpio_init_structure.Pin                               = GPIO_PIN_4;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Pull                              = GPIO_NOPULL;
   gpio_init_structure.Speed                             = GPIO_SPEED_FAST;
   gpio_init_structure.Alternate                         = GPIO_AF14_LTDC;
   HAL_GPIO_Init(GPIOE, &gpio_init_structure);

   /* GPIOG configuration */
   gpio_init_structure.Pin                               = GPIO_PIN_12;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Alternate                         = GPIO_AF9_LTDC;
   HAL_GPIO_Init(GPIOG, &gpio_init_structure);

   /* GPIOI LTDC alternate configuration */
   gpio_init_structure.Pin                               = GPIO_PIN_9 | GPIO_PIN_10 | \
                                                           GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Alternate                         = GPIO_AF14_LTDC;
   HAL_GPIO_Init(GPIOI, &gpio_init_structure);

   /* GPIOJ configuration */  
   gpio_init_structure.Pin                               = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | \
                                                           GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | \
                                                           GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11 | \
                                                           GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Alternate                         = GPIO_AF14_LTDC;
   HAL_GPIO_Init(GPIOJ, &gpio_init_structure);  

   /* GPIOK configuration */  
   gpio_init_structure.Pin                               = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_4 | \
                                                           GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
   gpio_init_structure.Mode                              = GPIO_MODE_AF_PP;
   gpio_init_structure.Alternate                         = GPIO_AF14_LTDC;
   HAL_GPIO_Init(GPIOK, &gpio_init_structure);

   /* LCD_DISP GPIO configuration */
   gpio_init_structure.Pin                               = GPIO_PIN_12;          /* LCD_DISP pin has to be manually controlled */
   gpio_init_structure.Mode                              = GPIO_MODE_OUTPUT_PP;
   HAL_GPIO_Init(GPIOI, &gpio_init_structure);

   /* LCD_BL_CTRL GPIO configuration */
   gpio_init_structure.Pin                               = GPIO_PIN_3;           /* LCD_BL_CTRL pin has to be manually controlled */
   gpio_init_structure.Mode                              = GPIO_MODE_OUTPUT_PP;
   HAL_GPIO_Init(GPIOK, &gpio_init_structure);

   /* Set LTDC Interrupt to the lowest priority */
   HAL_NVIC_SetPriority(LTDC_IRQn, 0xE, 0);

   /* Enable LTDC Interrupt */
   HAL_NVIC_EnableIRQ(LTDC_IRQn);
}

void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc)
{
   /* Reset peripherals */
   /* Enable LTDC reset state */
   __HAL_RCC_LTDC_FORCE_RESET();

   /* Release LTDC from reset state */ 
   __HAL_RCC_LTDC_RELEASE_RESET();
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
