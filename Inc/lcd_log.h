/**
  ******************************************************************************
  * lcd_log.h by duvallee.lee 2017
  ******************************************************************************
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef  __LCD_LOG_H__
#define  __LCD_LOG_H__

/* Includes ------------------------------------------------------------------*/

#include "lcd_log_conf.h"

void lcd_log_Init(volatile uint32_t* pframebuffer, uint32_t width, uint32_t height, uint32_t pixel_fmt);
void draw_char(uint8_t ch);

#endif /* __LCD_LOG_H__ */

