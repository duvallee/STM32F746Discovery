/*
 *
 * File : network_task.c
 *
 * Copyright (c) 2017 duvallee
 *
 */

#include <stdio.h>
#include "main.h"
#include "stm32f7xx_hal.h"
#include "debug_output.h"
#include "cmsis_os.h"

#include "lwip.h"
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"

#include "dhcp_ethernet.h"
#include "network_task.h"

// --------------------------------------------------------------------------
static struct netconn *g_tcp_con                         = NULL;

/* --------------------------------------------------------------------------
 * Name : network_tcp_server_task()
 *
 *
 * -------------------------------------------------------------------------- */
void network_tcp_task(void const* argument)
{
   while (1)
   {
      osDelay(1000);
//      debug_output_info(" \r\n");
   }
}

/* --------------------------------------------------------------------------
 * Name : network_tcp_server_task()
 *
 *
 * -------------------------------------------------------------------------- */
void network_tcp_server_task(void const* argument)
{
   debug_output_info("start !!! \r\n");
   struct netconn *server_conn, *newconn;
   err_t err, accept_err;
   struct netbuf *inbuf;
   err_t recv_err;
   char* buf;
   u16_t buflen;

   UNUSED(g_tcp_con);
   for (;;)
   {
      if (is_assigned_dhcp_address() != 0)
      {
         break;
      }
      osDelay(500);
   }

   // Create a new TCP connection handle
   server_conn                                           = netconn_new(NETCONN_TCP);

   if (server_conn == NULL)
   {
      debug_output_error("terminate tcp server !!! \r\n");
      return;
   }
   // Bind to port TCP_SERVER_PORT with default IP address
   err                                                   = netconn_bind(server_conn, NULL, TCP_SERVER_PORT);
   if (err != ERR_OK)
   {
      debug_output_error("cann't bind for tcp server !!! \r\n");
      return;
   }

   // Put the connection into LISTEN state
   netconn_listen(server_conn);

   while (1)
   {
      // accept any icoming connection
      accept_err                                         = netconn_accept(server_conn, &newconn);
      if (accept_err == ERR_OK)
      {
         debug_output_info(" connection TCP request \r\n");

         recv_err                                        = netconn_recv(newconn, &inbuf);
         if (recv_err == ERR_OK)
         {
            if (netconn_err(newconn) == ERR_OK) 
            {
               netbuf_data(inbuf, (void**) &buf, &buflen);
               debug_output_info("received byte %d : %s \r\n", buflen, buf);
            }
            netbuf_delete(inbuf);
         }
         netconn_write(newconn, "send message : server -> client", sizeof("send message : server -> client"), NETCONN_NOCOPY);

         // delete connection
         netconn_delete(newconn);
      }
      else if (accept_err == ERR_TIMEOUT)
      {
         debug_output_error("accept time-out !!! \r\n");
      }
      else if (accept_err == ERR_ABRT)
      {
         debug_output_error("accept abort !!! \r\n");
      }
      else if (accept_err == ERR_CLSD)
      {
      }
      else
      {
         debug_output_error("accept failed !!! : %d \r\n", accept_err);
      }

//      osDelay(1);
   }
}

/* --------------------------------------------------------------------------
 * Name : network_udp_server_task()
 *
 *
 * -------------------------------------------------------------------------- */
void network_udp_server_task(void const* argument)
{
   debug_output_info("start !!! \r\n");

   for (;;)
   {
      if (is_assigned_dhcp_address() != 0)
      {
         break;
      }
      osDelay(500);
   }

   while (1)
   {
      osDelay(1000);
//      debug_output_info(" \r\n");
   }
}



