/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

// -----------------------------------------------------------------------------
void _Error_Handler(char *, int);
#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

// -----------------------------------------------------------------------------
#define RK043FN48H_WIDTH                                 480                     // LCD Pixel Width
#define RK043FN48H_HEIGHT                                272                     // LCD Pixel Height

#define RK043FN48H_HSYNC                                 41                      // Horizontal Synchronization
#define RK043FN48H_HBP                                   13                      // Horizontal Back Porch
#define RK043FN48H_HFP                                   32                      // Horizontal Front Porch
#define RK043FN48H_VSYNC                                 10                      // Vertical Synchronization
#define RK043FN48H_VBP                                   2                       // Vertical Back Porch
#define RK043FN48H_VFP                                   2                       // Vertical Front Porch

// -----------------------------------------------------------------------------
// for GPIO
#define DISPLAY_CONTROL_PORT                             GPIOI
#define DISPLAY_CONTROL                                  GPIO_PIN_12

#define BACKLIGHT_CONTROL_PORT                           GPIOK
#define BACKLIGHT_CONTROL                                GPIO_PIN_3

// -----------------------------------------------------------------------------
// for Arduino UNO Connector

// -----------------------------------------------------------------------------
// Connector 4 - Pin 1 : USART6_RX (TIM3_CH2, TIM8_CH2, I2S3_MCK, USART6_RX...)
// 5V tolerant I/O
#define ARDUINO_CN4_PIN_01_PORT                          GPIOC
#define ARDUINO_CN4_PIN_01                               GPIO_PIN_7
#define ARDUINO_CN4_PIN_01_AF                            GPIO_AF8_USART6

// Connector 4 - Pin 2 : USART6_RX (TIM3_CH1, TIM8_CH1, I2S2_MCK, USART6_TX...)
// 5V tolerant I/O
#define ARDUINO_CN4_PIN_02_PORT                          GPIOC
#define ARDUINO_CN4_PIN_02                               GPIO_PIN_6
#define ARDUINO_CN4_PIN_02_AF                            GPIO_AF8_USART6

// Connector 4 - Pin 3 : 
// 5V tolerant I/O
#define ARDUINO_CN4_PIN_03_PORT                          GPIOG
#define ARDUINO_CN4_PIN_03                               GPIO_PIN_6
#define ARDUINO_CN4_PIN_03_AF

// Connector 4 - Pin 4 : (NJTRST, TIM3_CH1, SPI_MISO, SPI3_MISO, SPI2_NSS/I2S2_WS)
// 5V tolerant I/O
#define ARDUINO_CN4_PIN_04_PORT                          GPIOB
#define ARDUINO_CN4_PIN_04                               GPIO_PIN_4
#define ARDUINO_CN4_PIN_04_AF

// Connector 4 - Pin 5 : (USART6_CK)
// 5V tolerant I/O
#define ARDUINO_CN4_PIN_05_PORT                          GPIOG
#define ARDUINO_CN4_PIN_05                               GPIO_PIN_7
#define ARDUINO_CN4_PIN_05_AF

// Connector 4 - Pin 6 : (TIM5_CH4, SPI2_NSS/I2S_WS)
// 5V tolerant I/O
#define ARDUINO_CN4_PIN_06_PORT                          GPIOI
#define ARDUINO_CN4_PIN_06                               GPIO_PIN_0
#define ARDUINO_CN4_PIN_06_AF

// Connector 4 - Pin 7 : (I2C2_SMBA, SPI5_SCK,TIM12_CH1 ...)
// 5V tolerant I/O
#define ARDUINO_CN4_PIN_07_PORT                          GPIOH
#define ARDUINO_CN4_PIN_07                               GPIO_PIN_6
#define ARDUINO_CN4_PIN_07_AF

// Connector 4 - Pin 8 : (TIM8_ETR, SPI2_MOSI/I2S2_SD)
// 5V tolerant I/O
#define ARDUINO_CN4_PIN_08_PORT                          GPIOI
#define ARDUINO_CN4_PIN_08                               GPIO_PIN_3
#define ARDUINO_CN4_PIN_08_AF

// Connector 7 - Pin 1 : (TIM8_CH4, SPI2_MISO)
// 5V tolerant I/O
#define ARDUINO_CN7_PIN_01_PORT                          GPIOI
#define ARDUINO_CN7_PIN_01                               GPIO_PIN_2
#define ARDUINO_CN7_PIN_01_AF

// Connector 7 - Pin 2 : (JTDI, TIM2_CH1/TIM2_ETR, MDMI_CEC, SPI1_NSS/I2S1_WS, SPI3_NSS/I2S3_WS, UART4_RTS)
// 5V tolerant I/O
#define ARDUINO_CN7_PIN_02_PORT                          GPIOA
#define ARDUINO_CN7_PIN_02                               GPIO_PIN_15
#define ARDUINO_CN7_PIN_02_AF

// Connector 7 - Pin 3 : TIM1_CH1 (MCO1, TIM_CH1, TIM8_BKIN2, USART1_CK, OTG_FS_SOF...)
// 5V tolerant I/O
#define ARDUINO_CN7_PIN_03_PORT                          GPIOA
#define ARDUINO_CN7_PIN_03                               GPIO_PIN_8
#define ARDUINO_CN7_PIN_03_AF

// Connector 7 - Pin 4 : (RTC_REFIN, TIM1_CH3N, TIM8_CH_3N, SPI2_MOSI/I2S2_SD, TIM12_CH2 ...)
// 5V tolerant I/O
#define ARDUINO_CN7_PIN_04_PORT                          GPIOB
#define ARDUINO_CN7_PIN_04                               GPIO_PIN_15
#define ARDUINO_CN7_PIN_04_AF

// Connector 7 - Pin 5 : (TIM1_CH2N, TIM8_CH2N, SPI2_MISO, USART3_CTS, TIM12_CH1 ...)
// 5V tolerant I/O
#define ARDUINO_CN7_PIN_05_PORT                          GPIOB
#define ARDUINO_CN7_PIN_05                               GPIO_PIN_14
#define ARDUINO_CN7_PIN_05_AF

// Connector 7 - Pin 6 : LD1 (LED.GREEN) (TIM8_BKIN2, SPI2_SCK/I2S2_CK ...)
// 5V tolerant I/O
#define ARDUINO_CN7_PIN_06_PORT                          GPIOI
#define ARDUINO_CN7_PIN_06                               GPIO_PIN_1
#define ARDUINO_CN7_PIN_06_AF

// AVDD & GND : Pin 7 & Pin 8

// Connector 7 - Pin 9 : SDA (TIM4_CH4, TIM11_CH1, I2C1_SDA, SPI2_NSS/I2S2_WS, CAN1_TX ...)
// 5V tolerant I/O
#define ARDUINO_CN7_PIN_09_PORT                          GPIOB
#define ARDUINO_CN7_PIN_09                               GPIO_PIN_9
#define ARDUINO_CN7_PIN_09_AF

// Connector 7 - Pin 10 : SCL (TIM2_CH3, I2C2_SCL, SPI2_SCK/I2S2_CK, USART3_TX)
// 5V tolerant I/O
#define ARDUINO_CN7_PIN_10_PORT                          GPIOB
#define ARDUINO_CN7_PIN_10                               GPIO_PIN_8
#define ARDUINO_CN7_PIN_10_AF

// -----------------------------------------------------------------------------
// Connector 5 - Pin 1 : WakeUP (TIM2_CH1/TIM2_ETR, TIM5_CH1, TIM8_ETR, USART2_CTS, UART4_TX ...)
// 5V tolerant I/O
#define ARDUINO_CN5_PIN_01_PORT                          GPIOA
#define ARDUINO_CN5_PIN_01                               GPIO_PIN_0
#define ARDUINO_CN5_PIN_01_AF

// Connector 5 - Pin 2 : ( ...)
// 5V tolerant I/O
#define ARDUINO_CN5_PIN_02_PORT                          GPIOF
#define ARDUINO_CN5_PIN_02                               GPIO_PIN_10
#define ARDUINO_CN5_PIN_02_AF

// Connector 5 - Pin 3 : (SPI5_MOSI, SAI1_FS_B, UART7_CTS, TIM14_CH1, QUADSPI_BK1_IO1 ...)
// 5V tolerant I/O
#define ARDUINO_CN5_PIN_03_PORT                          GPIOF
#define ARDUINO_CN5_PIN_03                               GPIO_PIN_9
#define ARDUINO_CN5_PIN_03_AF

// Connector 5 - Pin 4 : (SPI5_MISO, SAI1_SCK_B, UART7_RTS, TIM13_CH1, QUADSPI_BK1_IO0 ...)
// 5V tolerant I/O
#define ARDUINO_CN5_PIN_04_PORT                          GPIOF
#define ARDUINO_CN5_PIN_04                               GPIO_PIN_8
#define ARDUINO_CN5_PIN_04_AF

// Connector 5 - Pin 5 : (TIM11_CH1, SPI5_SCK, SAI1_MCLK_B, UART7_TX ...)
// 5V tolerant I/O
#define ARDUINO_CN5_PIN_05_PORT                          GPIOF
#define ARDUINO_CN5_PIN_05                               GPIO_PIN_7
#define ARDUINO_CN5_PIN_05_AF

// Connector 5 - Pin 6 : (TIM10_CH1, SPI5_NSS, SAI_SD_B, UART7_RX ...)
// 5V tolerant I/O
#define ARDUINO_CN5_PIN_06_PORT                          GPIOF
#define ARDUINO_CN5_PIN_06                               GPIO_PIN_6
#define ARDUINO_CN5_PIN_06_AF

// -----------------------------------------------------------------------------
// LD1 ( shared with Connector 7 - Pin 6)
#define LED_1_GREEN_PORT                                 GPIOI
#define LED_1_GREEN                                      GPIO_PIN_1
#define LED_1_GREEN_AF


#endif /* __MAIN_H */

