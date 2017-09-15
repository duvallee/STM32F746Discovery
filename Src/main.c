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
#include "debug_output.h"

// #define USE_CLOCK_INTERNAL

// global variable
TIM_HandleTypeDef htim6;
UART_HandleTypeDef huart6;
LTDC_HandleTypeDef hltdc;
SDRAM_HandleTypeDef hsdram1;

#define MILLI_SECOND                                     1000
volatile uint32_t g_System_Start_Second                  = 0;
volatile uint16_t g_System_Start_Milli_Second            = 0;

#define FRAMEBUFFER_SIZE                                 (RK043FN48H_WIDTH * RK043FN48H_HEIGHT)

__IO uint32_t *g_FrameBuffer                             = (uint32_t *) 0xC0700000;
// volatile uint16_t g_FrameBuffer[FRAMEBUFFER_SIZE];

/* --------------------------------------------------------------------------
 * Name : _putc()
 *
 *
 * -------------------------------------------------------------------------- */
int _putc(unsigned char ch)
{
   if (HAL_UART_Transmit(&huart6, (uint8_t *) &ch, sizeof(ch), 0xFFFF) == HAL_OK)
   {
      return 0;
   }
   return -1;
}

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LTDC_Init(void);
static void MX_FMC_Init(void);
static void MX_USART6_UART_Init(void);
static void MX_TIM6_Init(void);

/* --------------------------------------------------------------------------
 * Name : main()
 *
 *
 * -------------------------------------------------------------------------- */
int main(void)
{
   GPIO_InitTypeDef GPIO_InitStruct;
   int i;

   HAL_Init();
   SystemClock_Config();

   MX_GPIO_Init();
   MX_FMC_Init();
   MX_USART6_UART_Init();
   MX_TIM6_Init();
   MX_LTDC_Init();

   // Clear FrameBuffer
   for (i = 0; i < FRAMEBUFFER_SIZE; i++)
   {
      g_FrameBuffer[i]                                   = 0x00000000;
   }

   /*Configure GPIO pin : PI1, D1 */
   GPIO_InitStruct.Pin                                   = GPIO_PIN_0;
   GPIO_InitStruct.Mode                                  = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull                                  = GPIO_NOPULL;
   GPIO_InitStruct.Speed                                 = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   /*Configure GPIO pin : PK3, backlight on */
   GPIO_InitStruct.Pin                                   = GPIO_PIN_0;
   GPIO_InitStruct.Mode                                  = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull                                  = GPIO_NOPULL;
   GPIO_InitStruct.Speed                                 = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

   /*Configure GPIO pin : PI1, D1
     Configure GPIO pin : PI12, Display on */
   GPIO_InitStruct.Pin                                   = GPIO_PIN_1 | GPIO_PIN_12;
   GPIO_InitStruct.Mode                                  = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull                                  = GPIO_NOPULL;
   GPIO_InitStruct.Speed                                 = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

   HAL_GPIO_WritePin(GPIOI, GPIO_PIN_12, GPIO_PIN_RESET);     // Display off
   HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_RESET);      // Backlight off

   debug_output_info("===================================================== \r\n");
   debug_output_info("BUILD   : %s %s \r\n", __DATE__, __TIME__);
   debug_output_info("VERSION : ver0.1.4 \r\n");
   debug_output_info("===================================================== \r\n");

   HAL_GPIO_WritePin(GPIOI, GPIO_PIN_12, GPIO_PIN_SET);     // Display on
   HAL_GPIO_WritePin(GPIOK, GPIO_PIN_3, GPIO_PIN_SET);      // Backlight on

   while (1)
   {
      debug_output_debug("Blue !!! \r\n");
      for (i = 0; i < FRAMEBUFFER_SIZE; i++)
      {
         g_FrameBuffer[i]                                = 0x000000FF;
      }
      HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);
      HAL_Delay(1000);

      debug_output_debug("Green !!! \r\n");
      for (i = 0; i < FRAMEBUFFER_SIZE; i++)
      {
         g_FrameBuffer[i]                                = 0x0000FF00;
      }
      HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);
      HAL_Delay(1000);

      debug_output_debug("Red !!! \r\n");
      for (i = 0; i < FRAMEBUFFER_SIZE; i++)
      {
         g_FrameBuffer[i]                                = 0x00FF0000;
      }
      HAL_GPIO_TogglePin(GPIOI, GPIO_PIN_1);
      HAL_Delay(1000);

   }
}


/* --------------------------------------------------------------------------
 * Name : HAL_SYSTICK_Callback()
 *
 *
 * -------------------------------------------------------------------------- */
void HAL_SYSTICK_Callback(void)
{
   g_System_Start_Milli_Second++;

   if (g_System_Start_Milli_Second >= MILLI_SECOND)
   {
      g_System_Start_Second++;
      g_System_Start_Milli_Second                        = 0;
   }

   if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == 0)
   {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
   }
   else
   {
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
   }
}

#if defined(USE_CLOCK_INTERNAL)
/* --------------------------------------------------------------------------
 * Name : SystemClock_Config()
 *        System Clock Configuration
 *
 * -------------------------------------------------------------------------- */
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
#else
void SystemClock_Config(void)
{
   RCC_OscInitTypeDef RCC_OscInitStruct;
   RCC_ClkInitTypeDef RCC_ClkInitStruct;

   /**Configure the main internal regulator output voltage 
   */
   __HAL_RCC_PWR_CLK_ENABLE();

   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

   /**Initializes the CPU, AHB and APB busses clocks 
   */
   RCC_OscInitStruct.OscillatorType                      = RCC_OSCILLATORTYPE_HSE;
   RCC_OscInitStruct.HSEState                            = RCC_HSE_ON;
   RCC_OscInitStruct.PLL.PLLState                        = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource                       = RCC_PLLSOURCE_HSE;
   RCC_OscInitStruct.PLL.PLLM                            = 25;
   RCC_OscInitStruct.PLL.PLLN                            = 400;
   RCC_OscInitStruct.PLL.PLLP                            = RCC_PLLP_DIV2;
   RCC_OscInitStruct.PLL.PLLQ                            = 2;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   /**Activate the Over-Drive mode 
   */
   if (HAL_PWREx_EnableOverDrive() != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   /**Initializes the CPU, AHB and APB busses clocks 
   */
   RCC_ClkInitStruct.ClockType                           = RCC_CLOCKTYPE_HCLK    |
                                                           RCC_CLOCKTYPE_SYSCLK  |
                                                           RCC_CLOCKTYPE_PCLK1   |
                                                           RCC_CLOCKTYPE_PCLK2;
   RCC_ClkInitStruct.SYSCLKSource                        = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider                       = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider                      = RCC_HCLK_DIV4;
   RCC_ClkInitStruct.APB2CLKDivider                      = RCC_HCLK_DIV2;

   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6) != HAL_OK)
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
#endif

/* --------------------------------------------------------------------------
 * Name : MX_LTDC_Init()
 *        LTDC init function
 *
 * -------------------------------------------------------------------------- */
static void MX_LTDC_Init(void)
{
   LTDC_LayerCfgTypeDef pLayerCfg;

   hltdc.Instance                                        = LTDC;
   hltdc.Init.HSPolarity                                 = LTDC_HSPOLARITY_AL;
   hltdc.Init.VSPolarity                                 = LTDC_VSPOLARITY_AL;
   hltdc.Init.DEPolarity                                 = LTDC_DEPOLARITY_AL;
   hltdc.Init.PCPolarity                                 = LTDC_PCPOLARITY_IPC;
   hltdc.Init.HorizontalSync                             = (RK043FN48H_HSYNC - 1);
   hltdc.Init.VerticalSync                               = (RK043FN48H_VSYNC - 1);
   hltdc.Init.AccumulatedHBP                             = (RK043FN48H_HSYNC + RK043FN48H_HBP - 1);;
   hltdc.Init.AccumulatedVBP                             = (RK043FN48H_VSYNC + RK043FN48H_VBP- 1);;
   hltdc.Init.AccumulatedActiveW                         = (RK043FN48H_WIDTH + RK043FN48H_HSYNC + RK043FN48H_HBP - 1);
   hltdc.Init.AccumulatedActiveH                         = (RK043FN48H_HEIGHT + RK043FN48H_VSYNC + RK043FN48H_VBP - 1);
   hltdc.Init.TotalWidth                                 = (RK043FN48H_WIDTH + RK043FN48H_HSYNC + RK043FN48H_HBP + RK043FN48H_HFP - 1);
   hltdc.Init.TotalHeigh                                 = (RK043FN48H_HEIGHT + RK043FN48H_VSYNC + RK043FN48H_VBP + RK043FN48H_VFP - 1);;
   hltdc.Init.Backcolor.Blue                             = 0;
   hltdc.Init.Backcolor.Green                            = 0;
   hltdc.Init.Backcolor.Red                              = 0;
   if (HAL_LTDC_Init(&hltdc) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   pLayerCfg.WindowX0                                    = 0;
   pLayerCfg.WindowX1                                    = (RK043FN48H_WIDTH - 1);
   pLayerCfg.WindowY0                                    = 0;
   pLayerCfg.WindowY1                                    = (RK043FN48H_HEIGHT - 1);
   pLayerCfg.PixelFormat                                 = LTDC_PIXEL_FORMAT_ARGB8888;
   pLayerCfg.Alpha                                       = 255;
   pLayerCfg.Alpha0                                      = 0;
   pLayerCfg.BlendingFactor1                             = LTDC_BLENDING_FACTOR1_CA;
   pLayerCfg.BlendingFactor2                             = LTDC_BLENDING_FACTOR2_CA;
   pLayerCfg.FBStartAdress                               = (uint32_t) g_FrameBuffer;
   pLayerCfg.ImageWidth                                  = RK043FN48H_WIDTH;
   pLayerCfg.ImageHeight                                 = RK043FN48H_HEIGHT;
   pLayerCfg.Backcolor.Blue                              = 0;
   pLayerCfg.Backcolor.Green                             = 0;
   pLayerCfg.Backcolor.Red                               = 0;
   if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

#if 0
#define LTDC_PIXEL_FORMAT_ARGB8888                  ((uint32_t)0x00000000U)      /*!< ARGB8888 LTDC pixel format */
#define LTDC_PIXEL_FORMAT_RGB888                    ((uint32_t)0x00000001U)      /*!< RGB888 LTDC pixel format   */
#endif

}


/* --------------------------------------------------------------------------
 * Name : BSP_SDRAM_Initialization_sequence()
 *
 *
 * -------------------------------------------------------------------------- */
#define SDRAM_MODEREG_BURST_LENGTH_1                     ((uint16_t) 0x0000)
#define SDRAM_MODEREG_BURST_LENGTH_2                     ((uint16_t) 0x0001)
#define SDRAM_MODEREG_BURST_LENGTH_4                     ((uint16_t) 0x0002)
#define SDRAM_MODEREG_BURST_LENGTH_8                     ((uint16_t) 0x0004)
#define SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL              ((uint16_t) 0x0000)
#define SDRAM_MODEREG_BURST_TYPE_INTERLEAVED             ((uint16_t) 0x0008)
#define SDRAM_MODEREG_CAS_LATENCY_2                      ((uint16_t) 0x0020)
#define SDRAM_MODEREG_CAS_LATENCY_3                      ((uint16_t) 0x0030)
#define SDRAM_MODEREG_OPERATING_MODE_STANDARD            ((uint16_t) 0x0000)
#define SDRAM_MODEREG_WRITEBURST_MODE_PROGRAMMED         ((uint16_t) 0x0000) 
#define SDRAM_MODEREG_WRITEBURST_MODE_SINGLE             ((uint16_t) 0x0200) 

#define SDRAM_TIMEOUT                                    ((uint32_t) 0xFFFF)

void BSP_SDRAM_Initialization_sequence(uint32_t RefreshCount)
{
   __IO uint32_t tmpmrd                                  = 0;
static FMC_SDRAM_CommandTypeDef Command;

   /* Step 1: Configure a clock configuration enable command */
   Command.CommandMode                                   = FMC_SDRAM_CMD_CLK_ENABLE;
   Command.CommandTarget                                 = FMC_SDRAM_CMD_TARGET_BANK1;
   Command.AutoRefreshNumber                             = 1;
   Command.ModeRegisterDefinition                        = 0;

   /* Send the command */
   HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

   /* Step 2: Insert 100 us minimum delay */ 
   /* Inserted delay is equal to 1 ms due to systick time base unit (ms) */
   HAL_Delay(1);

   /* Step 3: Configure a PALL (precharge all) command */ 
   Command.CommandMode                                   = FMC_SDRAM_CMD_PALL;
   Command.CommandTarget                                 = FMC_SDRAM_CMD_TARGET_BANK1;
   Command.AutoRefreshNumber                             = 1;
   Command.ModeRegisterDefinition                        = 0;

   /* Send the command */
   HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);  

   /* Step 4: Configure an Auto Refresh command */ 
   Command.CommandMode                                   = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
   Command.CommandTarget                                 = FMC_SDRAM_CMD_TARGET_BANK1;
   Command.AutoRefreshNumber                             = 8;
   Command.ModeRegisterDefinition                        = 0;

   /* Send the command */
   HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

   /* Step 5: Program the external memory mode register */
   tmpmrd                                                = (uint32_t) SDRAM_MODEREG_BURST_LENGTH_1          |  \
                                                                      SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL   |  \
                                                                      SDRAM_MODEREG_CAS_LATENCY_2           |  \
                                                                      SDRAM_MODEREG_OPERATING_MODE_STANDARD |  \
                                                                      SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;

   Command.CommandMode                                   = FMC_SDRAM_CMD_LOAD_MODE;
   Command.CommandTarget                                 = FMC_SDRAM_CMD_TARGET_BANK1;
   Command.AutoRefreshNumber                             = 1;
   Command.ModeRegisterDefinition                        = tmpmrd;

   /* Send the command */
   HAL_SDRAM_SendCommand(&hsdram1, &Command, SDRAM_TIMEOUT);

   /* Step 6: Set the refresh rate counter */
   /* Set the device refresh rate */
   HAL_SDRAM_ProgramRefreshRate(&hsdram1, RefreshCount); 
}

/* --------------------------------------------------------------------------
 * Name : MX_FMC_Init()
 *        FMC initialization function
 *
 * -------------------------------------------------------------------------- */
#define REFRESH_COUNT                                    ((uint32_t) 0x0603)     /* SDRAM refresh counter (100Mhz SD clock) */
static void MX_FMC_Init(void)
{
   FMC_SDRAM_TimingTypeDef SdramTiming;

   /** Perform the SDRAM1 memory initialization sequence
   */
   hsdram1.Instance                                      = FMC_SDRAM_DEVICE;
   /* hsdram1.Init */
   hsdram1.Init.SDBank                                   = FMC_SDRAM_BANK1;
   hsdram1.Init.ColumnBitsNumber                         = FMC_SDRAM_COLUMN_BITS_NUM_8;
   hsdram1.Init.RowBitsNumber                            = FMC_SDRAM_ROW_BITS_NUM_12;
   hsdram1.Init.MemoryDataWidth                          = FMC_SDRAM_MEM_BUS_WIDTH_16;
   hsdram1.Init.InternalBankNumber                       = FMC_SDRAM_INTERN_BANKS_NUM_4;
   hsdram1.Init.CASLatency                               = FMC_SDRAM_CAS_LATENCY_2;
   hsdram1.Init.WriteProtection                          = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
   hsdram1.Init.SDClockPeriod                            = FMC_SDRAM_CLOCK_PERIOD_2;
   hsdram1.Init.ReadBurst                                = FMC_SDRAM_RBURST_ENABLE;
   hsdram1.Init.ReadPipeDelay                            = FMC_SDRAM_RPIPE_DELAY_0;
   /* SdramTiming */
   SdramTiming.LoadToActiveDelay                         = 2;
   SdramTiming.ExitSelfRefreshDelay                      = 7;
   SdramTiming.SelfRefreshTime                           = 4;
   SdramTiming.RowCycleDelay                             = 7;
   SdramTiming.WriteRecoveryTime                         = 2;
   SdramTiming.RPDelay                                   = 2;
   SdramTiming.RCDDelay                                  = 2;

   if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK)
   {
      _Error_Handler(__FILE__, __LINE__);
   }

   BSP_SDRAM_Initialization_sequence(REFRESH_COUNT);
}


/* --------------------------------------------------------------------------
 * Name : MX_GPIO_Init()
 *
 *
 * -------------------------------------------------------------------------- */
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
   __HAL_RCC_GPIOB_CLK_ENABLE();
   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOD_CLK_ENABLE();
   __HAL_RCC_GPIOG_CLK_ENABLE();
   __HAL_RCC_GPIOH_CLK_ENABLE();
   __HAL_RCC_GPIOI_CLK_ENABLE();
   __HAL_RCC_GPIOK_CLK_ENABLE();
}

/* --------------------------------------------------------------------------
 * Name : MX_TIM6_Init()
 *
 *
 * -------------------------------------------------------------------------- */
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

/* --------------------------------------------------------------------------
 * Name : MX_USART6_UART_Init()
 *
 *
 * -------------------------------------------------------------------------- */
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

/* --------------------------------------------------------------------------
 * Name : _Error_Handler()
 *
 *
 * -------------------------------------------------------------------------- */
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

