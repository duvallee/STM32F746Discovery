/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
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
#include "stm32f7xx.h"
#include "stm32f7xx_it.h"
#include "cmsis_os.h"
#if defined(DEBUG_OUTPUT_USB)
#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
#endif

/* External variables --------------------------------------------------------*/
extern ETH_HandleTypeDef heth;
extern LTDC_HandleTypeDef hltdc;
extern DMA2D_HandleTypeDef hdma2d;

#if defined(DEBUG_OUTPUT_USB)
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
#endif
/******************************************************************************/
/*            Cortex-M7 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
   while (1)
   {
   }
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
   while (1)
   {
   }
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
   while (1)
   {
   }
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
   while (1)
   {
   }
}

#if 0    // move to the FreeRTOS
/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
}
#endif

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
}

#if 0    // move to the FreeRTOS
/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
}
#endif

/**
* @brief This function handles System tick timer.
*/

void SysTick_Handler(void)
{
   HAL_IncTick();
   HAL_SYSTICK_IRQHandler();

   osSystickHandler();
}

/**
  * @brief  This function handles LTDC global interrupt request.
  * @param  None
  * @retval None
  */
void LTDC_IRQHandler(void)
{
   HAL_LTDC_IRQHandler(&hltdc);
}

/**
* @brief This function handles EXTI line[15:10] interrupts.
*/
void EXTI15_10_IRQHandler(void)
{
   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_13) != 0)
   {
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
   }

   if (__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_12) != 0)
   {
      HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_12);
   }
 }

/******************************************************************************/
/* STM32F7xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f7xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles Ethernet global interrupt.
*/
void ETH_IRQHandler(void)
{
   HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_6);
   HAL_ETH_IRQHandler(&heth);
}

#if defined(DEBUG_OUTPUT_USB)
/**
* @brief This function handles USB On The Go FS global interrupt.
*/
void OTG_FS_IRQHandler(void)
{
   HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
}

#endif


