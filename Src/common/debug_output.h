/*
File: debug_output.h

Copyright (c) duvallee
*/

#ifndef __DEBUG_OUTPUT_H__
#define __DEBUG_OUTPUT_H__

#include "printf.h"

#define DEBUG_STRING_LEVEL_ERROR
#define DEBUG_STRING_LEVEL_WARN
#define DEBUG_STRING_LEVEL_DEBUG
#define DEBUG_STRING_LEVEL_FN_TRACE
#define DEBUG_STRING_LEVEL_INFO

#if defined(DEBUG_STRING_LEVEL_ERROR)
#define debug_output_error(fmt, ...)                                             \
         printf("[%06d.%03d:%s-%s-%d-ERROR] " fmt,                               \
                                             (int) g_System_Start_Second,        \
                                             (int) g_System_Start_Milli_Second,  \
                                             __FILE__,                           \
                                             __func__,                           \
                                             (int) __LINE__,                     \
                                             ##__VA_ARGS__);                     \
                                             /* end of ... */
#else
#define debug_output_error(fmt, ...)         asm("nop")
#endif

#if defined(DEBUG_STRING_LEVEL_WARN)
#define debug_output_warn(fmt, ...)                                              \
         printf("[%06d.%03d:%s-%s-%d-WARN ] " fmt,                               \
                                             (int) g_System_Start_Second,        \
                                             (int) g_System_Start_Milli_Second,  \
                                             __FILE__,                           \
                                             __func__,                           \
                                             (int) __LINE__,                     \
                                             ##__VA_ARGS__);                     \
                                             /* end of ... */
#else
#define debug_output_warn(fmt, ...)          asm("nop")
#endif

#if defined(DEBUG_STRING_LEVEL_DEBUG)
#define debug_output_debug(fmt, ...)                                             \
         printf("[%06d.%03d:%s-%s-%d-DEBUG] " fmt,                               \
                                             (int) g_System_Start_Second,        \
                                             (int) g_System_Start_Milli_Second,  \
                                             __FILE__,                           \
                                             __func__,                           \
                                             (int) __LINE__,                     \
                                             ##__VA_ARGS__);                     \
                                             /* end of ... */
#else
#define debug_output_debug(fmt, ...)         asm("nop")
#endif

#if defined(DEBUG_STRING_LEVEL_FN_TRACE)
#define debug_output_fn(fmt, ...)                                                \
         printf("[%06d.%03d:%s-%s-%d-FN   ] " fmt,                               \
                                             (int) g_System_Start_Second,        \
                                             (int) g_System_Start_Milli_Second,  \
                                             __FILE__,                           \
                                             __func__,                           \
                                             (int) __LINE__,                     \
                                             ##__VA_ARGS__);                     \
                                             /* end of ... */
#else
#define debug_output_fn(fmt, ...)            asm("nop")
#endif

#if defined(DEBUG_STRING_LEVEL_INFO)
#define debug_output_info(fmt, ...)                                              \
         printf("[%06d.%03d:%s-%s-%d-INFO ] " fmt,                               \
                                             (int) g_System_Start_Second,        \
                                             (int) g_System_Start_Milli_Second,  \
                                             __FILE__,                           \
                                             __func__,                           \
                                             (int) __LINE__,                     \
                                             ##__VA_ARGS__);                     \
                                             /* end of ... */
#else
#define debug_output_info(fmt, ...)          asm("nop")
#endif


extern volatile uint32_t g_System_Start_Second;
extern volatile uint16_t g_System_Start_Milli_Second;

#endif      // __PRINTF_H__

