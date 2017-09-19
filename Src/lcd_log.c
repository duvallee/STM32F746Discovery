/**
  ******************************************************************************
  * lcd_log.c by duvallee.lee 2017
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f7xx_hal.h"
#include "debug_output.h"
#include "lcd_log.h"

typedef struct _LCD_LOG_FONT_INFO
{
   sFONT* font_info;

   uint32_t f_color;
   uint32_t b_color;

   uint16_t xpos;
   uint16_t ypos;

   uint8_t char_width;
   uint8_t char_height;   

   uint32_t char_num;
   uint32_t line_num;
} LCD_LOG_FONT_INFO;

volatile uint32_t* g_pFrameBuffer                        = NULL;
uint32_t g_width                                         = 0;
uint32_t g_height                                        = 0;
uint32_t g_pixel_fmt                                     = 0;
LCD_LOG_FONT_INFO g_lcd_log_font_info;


/* --------------------------------------------------------------------------
 * Name : lcd_clear()
 *
 *
 * -------------------------------------------------------------------------- */
void lcd_clear(uint32_t RGB_Color)
{
   int i;
   if (g_pixel_fmt == LTDC_PIXEL_FORMAT_ARGB8888)
   {
      volatile uint32_t* pFrameBuffer                    = g_pFrameBuffer;
      for (i = 0; i < (g_width * g_height); i++)
      {
         pFrameBuffer[i]                                 = RGB_Color;
      }
   }
   else if (g_pixel_fmt == LTDC_PIXEL_FORMAT_RGB888)
   {
      volatile uint8_t* pFrameBuffer                     = (volatile uint8_t*) g_pFrameBuffer;
      for (i = 0; i < (g_width * g_height * 3); i++)
      {
         pFrameBuffer[i]                                 = RGB_Color;
      }
   }
   else if (g_pixel_fmt == LTDC_PIXEL_FORMAT_RGB565)
   {
      volatile uint16_t* pFrameBuffer                    = (volatile uint16_t*) g_pFrameBuffer;
      for (i = 0; i < (g_width * g_height); i++)
      {
         pFrameBuffer[i]                                 = RGB_Color;
      }
   }
}

/* --------------------------------------------------------------------------
 * Name : draw_Pixel()
 *
 *
 * -------------------------------------------------------------------------- */
void draw_Pixel(uint16_t xpos, uint16_t ypos, uint32_t RGB_Color)
{
   if (g_pixel_fmt == LTDC_PIXEL_FORMAT_ARGB8888)
   {
      volatile uint32_t* pFrameBuffer                    = g_pFrameBuffer;
      *(pFrameBuffer + ((ypos * g_width + xpos)))        = RGB_Color;
   }
   else if (g_pixel_fmt == LTDC_PIXEL_FORMAT_RGB888)
   {
      volatile uint8_t* pFrameBuffer                     = (volatile uint8_t*) g_pFrameBuffer;
      *(pFrameBuffer + (3 * (ypos * g_width + xpos)))    = ((RGB_Color >> 16) & 0xFF);
      *(pFrameBuffer + (3 * (ypos * g_width + xpos)) + 1)= ((RGB_Color >>  8) & 0xFF);
      *(pFrameBuffer + (3 * (ypos * g_width + xpos)) + 2)= (RGB_Color & 0xFF);
   }
   else if (g_pixel_fmt == LTDC_PIXEL_FORMAT_RGB565)
   {
      volatile uint16_t* pFrameBuffer                    = (volatile uint16_t*) g_pFrameBuffer;
      *(pFrameBuffer + ((ypos * g_width + xpos)))        = RGB_Color;
   }
}

/* --------------------------------------------------------------------------
 * Name : draw_pixel_char()
 *
 *
 * -------------------------------------------------------------------------- */
void draw_pixel_char(uint16_t xpos, uint16_t ypos, uint8_t ch)
{
   // start index 0x20(' ', space char)
   int height                                            = 0;
   int width                                             = 0;
   uint16_t ch_index                                     = ((ch - ' ') * g_lcd_log_font_info.font_info->Height);

   for (height = 0; height < g_lcd_log_font_info.font_info->Height; height++)
   {
      for (width = 0; width < g_lcd_log_font_info.font_info->Width; width++)
      {
         if (((g_lcd_log_font_info.font_info->table[ch_index + height] << width) & 0x80) == 0x80)
         {
            draw_Pixel(xpos + width, ypos + height + 2, g_lcd_log_font_info.f_color);
         }
         else
         {
            draw_Pixel(xpos + width, ypos + height + 2, g_lcd_log_font_info.b_color);
         }
      }
   }
}


/* --------------------------------------------------------------------------
 * Name : scroll_line()
 *
 *
 * -------------------------------------------------------------------------- */
void scroll_line()
{
   int x                                                 = 0;
   int line                                              = 0;
   int y                                                 = 0;

   if (g_pixel_fmt == LTDC_PIXEL_FORMAT_ARGB8888)
   {
      volatile uint32_t* pFrameBuffer                    = g_pFrameBuffer;
      for (line = 1; line <= g_lcd_log_font_info.line_num; line++)
      {
         for (y = 0; y < g_lcd_log_font_info.char_height; y++)
         {
            for (x = 0; x < g_width; x++)
            {
               *(pFrameBuffer + ((((((line - 1) * g_lcd_log_font_info.char_height) + y) * g_width) + x))) 
                                                   = *(pFrameBuffer + (((((line * g_lcd_log_font_info.char_height) + y) * g_width) + x)));
            }
         }
      }
      // last line
      for (y = 0; y < g_lcd_log_font_info.char_height; y++)
      {
         for (x = 0; x < g_width; x++)
         {
            *(pFrameBuffer + (((((g_lcd_log_font_info.line_num * g_lcd_log_font_info.char_height) + y) * g_width) + x))) 
                                                = g_lcd_log_font_info.b_color;
         }
      }
   }
   else if (g_pixel_fmt == LTDC_PIXEL_FORMAT_RGB888)
   {
//      volatile uint8_t* pFrameBuffer                     = (volatile uint8_t*) g_pFrameBuffer;
//      for (i = 0; i < (g_width * g_height * 3); i++)
//      {
//         pFrameBuffer[i]                                 = RGB_Color;
//      }
   }
   else if (g_pixel_fmt == LTDC_PIXEL_FORMAT_RGB565)
   {
//      volatile uint16_t* pFrameBuffer                    = (volatile uint16_t*) g_pFrameBuffer;
//      for (i = 0; i < (g_width * g_height); i++)
//      {
//         pFrameBuffer[i]                                 = RGB_Color;
//      }
   }
}

/* --------------------------------------------------------------------------
 * Name : draw_char()
 *
 *
 * -------------------------------------------------------------------------- */
void draw_char(uint8_t ch)
{
   uint16_t xpos                                         = 0;
   uint16_t ypos                                         = 0;

   if (ch == '\r')
   {
      return;
   }
   if (ch == '\n')
   {
      g_lcd_log_font_info.xpos                           = 0;
      g_lcd_log_font_info.ypos++;
      return;
   }

   if (g_lcd_log_font_info.xpos >= g_lcd_log_font_info.char_num)
   {
      g_lcd_log_font_info.xpos                           = 0;
      g_lcd_log_font_info.ypos++;
   }

   if (g_lcd_log_font_info.ypos > g_lcd_log_font_info.line_num)
   {
      scroll_line();
      g_lcd_log_font_info.ypos                           = g_lcd_log_font_info.line_num;
   }

   xpos                                                  = g_lcd_log_font_info.xpos * g_lcd_log_font_info.char_width;
   ypos                                                  = g_lcd_log_font_info.ypos * g_lcd_log_font_info.char_height;

   draw_pixel_char(xpos, ypos, ch);

   g_lcd_log_font_info.xpos++;
}


/* --------------------------------------------------------------------------
 * Name : lcd_log_Init()
 *
 *
 * -------------------------------------------------------------------------- */
void lcd_log_Init(volatile uint32_t* pframebuffer, uint32_t width, uint32_t height, uint32_t pixel_fmt)
{
   g_pFrameBuffer                                        = pframebuffer;
   g_width                                               = width;
   g_height                                              = height;
   g_pixel_fmt                                           = pixel_fmt;

   g_lcd_log_font_info.font_info                         = &Font12;
   g_lcd_log_font_info.f_color                           = 0xFFFFFF;
   g_lcd_log_font_info.b_color                           = 0x000000;

   g_lcd_log_font_info.xpos                              = 0;
   g_lcd_log_font_info.ypos                              = 0;

   g_lcd_log_font_info.char_width                        = g_lcd_log_font_info.font_info->Width + 2;
   g_lcd_log_font_info.char_height                       = g_lcd_log_font_info.font_info->Height + 2;

   g_lcd_log_font_info.char_num                          = (g_width / g_lcd_log_font_info.char_width);
   g_lcd_log_font_info.line_num                          = (g_height / g_lcd_log_font_info.char_height) - 1;

   lcd_clear(g_lcd_log_font_info.b_color);

#if 0
   debug_output_info("width  : %d \r\n", g_width);
   debug_output_info("height : %d \r\n", g_height);

   debug_output_info("font width  : %d \r\n", g_lcd_log_font_info.char_width);
   debug_output_info("font height : %d \r\n", g_lcd_log_font_info.char_height);

   debug_output_info("character  : %d \r\n", g_lcd_log_font_info.char_num);
   debug_output_info("line : %d \r\n", g_lcd_log_font_info.line_num);

   {
      int x, y;
      char ch = ' ';
      for (y = 0; y < (272 - g_lcd_log_font_info.char_height) ; y += g_lcd_log_font_info.char_height)
      {
         for (x = 0; x < (480 - g_lcd_log_font_info.char_width); x += g_lcd_log_font_info.char_width)
         {
            draw_pixel_char(x, y, ch);
            ch++;
            if (ch > 127)
            {
               ch = ' ';
            }
         }
      }
   }
#endif
}

