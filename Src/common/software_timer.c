/*
File: software_timer.c

Copyright (c) duvallee
*/

#include <stdio.h>
#include "main.h"
#include "stm32f7xx_hal.h"
#include "debug_output.h"
#include "software_timer.h"

#define MAX_SOFTWARE_TIMER                               32
#define MILLI_SECOND                                     1000

// defined in main.c file
extern volatile uint32_t g_System_Start_Second;
extern volatile uint16_t g_System_Start_Milli_Second;

typedef struct _SOFTWARE_TIMER_STRUCT
{
   uint8_t timer_index;
   uint32_t last_call_second;
   uint16_t last_call_milli_second;

   uint32_t ms_elapse;
   int call_count;
   int call_fn_count;

   SOFTWARE_TIMER_FN fn_timer;

   void* pPrivate_Data;
} SOFTWARE_TIMER_STRUCT;

// -----------------------------------------------------------------------------
// global variable
static SOFTWARE_TIMER_STRUCT g_Software_Timer[MAX_SOFTWARE_TIMER] = {0, };

/* --------------------------------------------------------------------------
 * Name : init_software_timer()
 *
 *
 * -------------------------------------------------------------------------- */
void init_software_timer()
{
   int i;
   for (i = 0; i < MAX_SOFTWARE_TIMER; i++)
   {
      g_Software_Timer[i].timer_index                    = 0;
      g_Software_Timer[i].last_call_second               = 0;
      g_Software_Timer[i].last_call_milli_second         = 0;
      g_Software_Timer[i].ms_elapse                      = 0;
      g_Software_Timer[i].call_count                     = 0;
      g_Software_Timer[i].call_fn_count                  = 0;
      g_Software_Timer[i].fn_timer                       = 0;
      g_Software_Timer[i].pPrivate_Data                  = 0;
   }
}

/* --------------------------------------------------------------------------
 * Name : proc_software_timer()
 *
 *
 * -------------------------------------------------------------------------- */
void proc_software_timer()
{
   int i;
   uint32_t current_milli_second                         = (g_System_Start_Second * MILLI_SECOND) + g_System_Start_Milli_Second;
   uint32_t target_milli_second                          = 0;
   for (i = 0; i < MAX_SOFTWARE_TIMER; i++)
   {
      if (g_Software_Timer[i].timer_index != 0)
      {
         target_milli_second                             = (g_Software_Timer[i].last_call_second * MILLI_SECOND) +
                                                            g_Software_Timer[i].last_call_milli_second +
                                                            g_Software_Timer[i].ms_elapse;
         if (target_milli_second <= current_milli_second)
         {
            g_Software_Timer[i].last_call_second         = g_System_Start_Second;
            g_Software_Timer[i].last_call_milli_second   = g_System_Start_Milli_Second;
            if (g_Software_Timer[i].call_count < 0)
            {
               (*(g_Software_Timer[i].fn_timer))(g_Software_Timer[i].pPrivate_Data);
            }
            else if (g_Software_Timer[i].call_count == g_Software_Timer[i].call_fn_count)
            {
               // delete timer
               g_Software_Timer[i].timer_index           = 0;
            }
            else
            {
               (*(g_Software_Timer[i].fn_timer))(g_Software_Timer[i].pPrivate_Data);
               g_Software_Timer[i].call_fn_count++;
            }
         }
      }
   }
}

/* --------------------------------------------------------------------------
 * Name : add_software_timer()
 *
 *
 * -------------------------------------------------------------------------- */
uint32_t add_software_timer(SOFTWARE_TIMER_FN fn, uint32_t ms_elapse, int count, void* private_data)
{
   int i;
   for (i = 0; i < MAX_SOFTWARE_TIMER; i++)
   {
      if (g_Software_Timer[i].timer_index == 0)
      {
         g_Software_Timer[i].timer_index                 = i + 1;
         g_Software_Timer[i].last_call_second            = g_System_Start_Second;
         g_Software_Timer[i].last_call_milli_second      = g_System_Start_Milli_Second;
         g_Software_Timer[i].ms_elapse                   = ms_elapse;
         g_Software_Timer[i].call_count                  = count;
         g_Software_Timer[i].call_fn_count               = 0;
         g_Software_Timer[i].fn_timer                    = fn;
         g_Software_Timer[i].pPrivate_Data               = private_data;

         debug_output_info("ID : %d \r\n", g_Software_Timer[i].timer_index);
         return (g_Software_Timer[i].timer_index);
      }
   }
   return 0;
}

/* --------------------------------------------------------------------------
 * Name : delete_software_timer()
 *
 *
 * -------------------------------------------------------------------------- */
void delete_software_timer(uint32_t timer_index)
{
   int i;
   for (i = 0; i < MAX_SOFTWARE_TIMER; i++)
   {
      if (g_Software_Timer[i].timer_index == timer_index)
      {
         g_Software_Timer[i].timer_index                 = 0;
         return;
      }
   }
}



