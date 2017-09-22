/*
File: software_timer.h

Copyright (c) duvallee
*/

#ifndef __SOFTWARE_TIMER_H__
#define __SOFTWARE_TIMER_H__

typedef void (*SOFTWARE_TIMER_FN)(void*);

void init_software_timer();
void proc_software_timer();

uint32_t add_software_timer(SOFTWARE_TIMER_FN fn, uint32_t ms_elapse, int count, void* private_data);
void delete_software_timer(uint32_t timer_index);

#endif      // __SOFTWARE_TIMER_H__

