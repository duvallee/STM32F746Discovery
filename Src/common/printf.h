/*
File: printf.h

Copyright (c) duvallee
*/

#ifndef __PRINTF_H__
#define __PRINTF_H__
#pragma once
#include <stdarg.h>

#define printf                                           tfp_printf
int tfp_printf(const char *fmt, ...);

#endif      // __PRINTF_H__

