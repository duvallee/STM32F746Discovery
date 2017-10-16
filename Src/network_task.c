
/*
 *
 * File : network_task.c
 *
 * Copyright (c) duvallee
 *
*/


#include <stdio.h>
#include "main.h"
#include "stm32f7xx_hal.h"
#include "debug_output.h"
#include "cmsis_os.h"

#include "lwip.h"


/* --------------------------------------------------------------------------
 * Name : network_task()
 *
 *
 * -------------------------------------------------------------------------- */
void network_task(void const* argument)
{
   debug_output_info("start !!! \r\n");
   /* Create tcp_ip stack thread */
//   tcpip_init(NULL, NULL);
//   lwip_init();


   while (1)
   {
      osDelay(100);
//      debug_output_info("network_task \r\n");
   }
}




