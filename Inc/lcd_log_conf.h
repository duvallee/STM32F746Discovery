/**
  ******************************************************************************
  * @file    USB_Host/DualCore_Standalone/Inc/lcd_log_conf.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    30-December-2016
  * @brief   LCD Log configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics International N.V. 
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __LCD_LOG_CONF_H__
#define  __LCD_LOG_CONF_H__

#include "fonts.h"

#define LCD_COLOR_BLUE                                   ((uint32_t) 0xFF0000FF)
#define LCD_COLOR_GREEN                                  ((uint32_t) 0xFF00FF00)
#define LCD_COLOR_RED                                    ((uint32_t) 0xFFFF0000)
#define LCD_COLOR_CYAN                                   ((uint32_t) 0xFF00FFFF)
#define LCD_COLOR_MAGENTA                                ((uint32_t) 0xFFFF00FF)
#define LCD_COLOR_YELLOW                                 ((uint32_t) 0xFFFFFF00)
#define LCD_COLOR_LIGHTBLUE                              ((uint32_t) 0xFF8080FF)
#define LCD_COLOR_LIGHTGREEN                             ((uint32_t) 0xFF80FF80)
#define LCD_COLOR_LIGHTRED                               ((uint32_t) 0xFFFF8080)
#define LCD_COLOR_LIGHTCYAN                              ((uint32_t) 0xFF80FFFF)
#define LCD_COLOR_LIGHTMAGENTA                           ((uint32_t) 0xFFFF80FF)
#define LCD_COLOR_LIGHTYELLOW                            ((uint32_t) 0xFFFFFF80)
#define LCD_COLOR_DARKBLUE                               ((uint32_t) 0xFF000080)
#define LCD_COLOR_DARKGREEN                              ((uint32_t) 0xFF008000)
#define LCD_COLOR_DARKRED                                ((uint32_t) 0xFF800000)
#define LCD_COLOR_DARKCYAN                               ((uint32_t) 0xFF008080)
#define LCD_COLOR_DARKMAGENTA                            ((uint32_t) 0xFF800080)
#define LCD_COLOR_DARKYELLOW                             ((uint32_t) 0xFF808000)
#define LCD_COLOR_WHITE                                  ((uint32_t) 0xFFFFFFFF)
#define LCD_COLOR_LIGHTGRAY                              ((uint32_t) 0xFFD3D3D3)
#define LCD_COLOR_GRAY                                   ((uint32_t) 0xFF808080)
#define LCD_COLOR_DARKGRAY                               ((uint32_t) 0xFF404040)
#define LCD_COLOR_BLACK                                  ((uint32_t) 0xFF000000)
#define LCD_COLOR_BROWN                                  ((uint32_t) 0xFFA52A2A)
#define LCD_COLOR_ORANGE                                 ((uint32_t) 0xFFFFA500)
#define LCD_COLOR_TRANSPARENT                            ((uint32_t) 0xFF000000)

/* Define the LCD default text color */
#define LCD_LOG_DEFAULT_COLOR                            LCD_COLOR_WHITE

/* Comment the line below to disable the scroll back and forward features */
#define LCD_SCROLL_ENABLED                               1

/* Define the Fonts  */
#define LCD_LOG_HEADER_FONT                              Font16
#define LCD_LOG_FOOTER_FONT                              Font12
#define LCD_LOG_TEXT_FONT                                Font12
            
/* Define the LCD LOG Color  */
#define LCD_LOG_BACKGROUND_COLOR                         LCD_COLOR_BLACK
#define LCD_LOG_TEXT_COLOR                               LCD_COLOR_WHITE

#define LCD_LOG_SOLID_BACKGROUND_COLOR                   LCD_COLOR_BLUE
#define LCD_LOG_SOLID_TEXT_COLOR                         LCD_COLOR_WHITE

/* Define the cache depth */
#define CACHE_SIZE                                       100
#define YWINDOW_SIZE                                     13

#if (YWINDOW_SIZE > 13)
  #error "Wrong YWINDOW SIZE"
#endif

#endif /* __LCD_LOG_CONF_H */


