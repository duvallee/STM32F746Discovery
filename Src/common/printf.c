/*
File: printf.h

Copyright (c) duvallee
*/


#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>

#include "printf.h"

#include "stm32f7xx_hal.h"



int _putc(unsigned char ch);


/* --------------------------------------------------------------------------
 * Name : a2d()
 *
 *
 * -------------------------------------------------------------------------- */
int a2d(char ch)
{
   if (ch >= '0' && ch <= '9')
   {
      return ch - '0';
   }
   else if (ch >= 'a' && ch <= 'f')
   {
      return ch - 'a' + 10;
   }
   else if (ch >= 'A' && ch <= 'F')
   {
      return ch - 'A' + 10;
   }
   else
   {
      return -1;
   }
}


/* --------------------------------------------------------------------------
 * Name : a2i()
 *
 *
 * -------------------------------------------------------------------------- */
char a2i(char ch, const char **src, int base, int *nump)
{
   const char *p                                         = *src;
   int num                                               = 0;
   int digit;
   while ((digit = a2d(ch)) >= 0)
   {
      if (digit > base)
      {
         break;
      }
      num                                                = num * base + digit;
      ch                                                 = *p++;
   }
   *src                                                  = p;
   *nump                                                 = num;
   return ch;
}

/* --------------------------------------------------------------------------
 * Name : ui2a()
 *
 *
 * -------------------------------------------------------------------------- */
void ui2a(unsigned int num, unsigned int base, int uc, char *bf)
{
   unsigned int d                                        = 1;

   while (num / d >= base)
   {
      d                                                  *= base;
   }

   while (d != 0)
   {
      int dgt                                            = num / d;
      *bf++                                              = dgt + (dgt < 10 ? '0' : (uc ? 'A' : 'a') - 10);

      // Next digit
      num                                                %= d;
      d                                                  /= base;
   }
   *bf                                                   = 0;
}

/* --------------------------------------------------------------------------
 * Name : i2a()
 *
 *
 * -------------------------------------------------------------------------- */
void i2a(int num, char *bf)
{
   if (num < 0)
   {
      num                                                = -num;
      *bf++                                              = '-';
   }
   ui2a(num, 10, 0, bf);
}



/* --------------------------------------------------------------------------
 * Name : putchw()
 *
 *
 * -------------------------------------------------------------------------- */
static int putchw(int n, char z, char *bf)
{
   int written                                           = 0;
   char fc                                               = z ? '0' : ' ';
   char ch;
   char *p                                               = bf;
   while (*p++ && n > 0)
   n--;
   while (n-- > 0)
   {
      _putc(fc);
      written++;
   }
   while ((ch = *bf++))
   {
      _putc(ch);
      written++;
   }
   return written;
}


/* --------------------------------------------------------------------------
 * Name : tfp_format()
 *      retrun number of bytes written
 *
 * -------------------------------------------------------------------------- */
int tfp_format(const char *fmt, va_list va)
{
   char bf[12];
   int written                                           = 0;
   char ch;

   while ((ch = *(fmt++)))
   {
      if (ch != '%')
      {
         _putc(ch);
         written++;
      }
      else
      {
         char lz                                         = 0;
         int w                                           = 0;
         ch                                              = *(fmt++);
         if (ch == '0')
         {
            ch                                           = *(fmt++);
            lz                                           = 1;
         }

         if (ch >= '0' && ch <= '9')
         {
            ch                                           = a2i(ch, &fmt, 10, &w);
         }
         switch (ch)
         {
            case 0 :
               return written;

            case 'u' :
            {
               ui2a(va_arg(va, unsigned int), 10, 0, bf);
               written                                   += putchw(w, lz, bf);
               break;
            }

            case 'd':
            {
               i2a(va_arg(va, int), bf);
               written                                   += putchw(w, lz, bf);
               break;
            }
            case 'x' :
            case 'X' :
               ui2a(va_arg(va, unsigned int), 16, (ch == 'X'), bf);
               written                                   += putchw(w, lz, bf);
               break;

            case 'c' :
               _putc((char) (va_arg(va, int)));
               written++;
               break;

            case 's' :
               written                                   += putchw(w, 0, va_arg(va, char *));
               break;

            case '%' :
               _putc(ch);
               written++;
               break;

            case 'n' :
               *va_arg(va, int*)                         = written;
               break;

            default:
               break;
         }
      }
   }

   return written;
}

/* --------------------------------------------------------------------------
 * Name : tfp_printf()
 *
 *
 * -------------------------------------------------------------------------- */
int tfp_printf(const char *fmt, ...)
{
   va_list va;
   va_start(va, fmt);
   int written                                           = tfp_format(fmt, va);
   va_end(va);

   return written;
}






