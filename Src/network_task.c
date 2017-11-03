/*
 *
 * File : network_task.c
 *
 * Copyright (c) 2017 duvallee
 *
 */

#include <stdio.h>
#include <string.h>
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
static struct netconn *g_udp_con                         = NULL;

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
   err_t recv_err, send_err;
   struct netbuf *inbuf                                  = NULL;
   struct netbuf *outbuf                                 = NULL;
   err_t err;
   char* buf;
   u16_t buflen;

   for (;;)
   {
      if (is_assigned_dhcp_address() != 0)
      {
         break;
      }
      osDelay(500);
   }

   // Create a new UDP connection handle
   g_udp_con                                             = netconn_new(NETCONN_UDP);

   if (g_udp_con == NULL)
   {
      debug_output_error("terminate udp server because cann't create socket for UDP !!! \r\n");
      return;
   }

   // Bind to port UDP_SERVER_PORT with default IP address
   err                                                   = netconn_bind(g_udp_con, NULL, UDP_SERVER_PORT);
   if (err != ERR_OK)
   {
      debug_output_error("cann't bind for udp !!! \r\n");
      return;
   }

   while (1)
   {
      recv_err                                        = netconn_recv(g_udp_con, &inbuf);
      if (recv_err == ERR_OK)
      {
         if (netconn_err(g_udp_con) == ERR_OK) 
         {
            netbuf_data(inbuf, (void**) &buf, &buflen);
            debug_output_info("received byte %d : %s (%s) \r\n", buflen, buf, ipaddr_ntoa(&(inbuf->addr)));
         }
      }
      outbuf                                    = netbuf_new();
      buflen                                    = sizeof("send udp response message : hellow world !!!") + 1;
      buf                                       = (char*) netbuf_alloc(outbuf, buflen);

      memset((void*) buf, 0, (size_t) buflen);
      sprintf(buf, "send udp response message : hellow world !!!");

      ip_addr_set(&(outbuf->addr), &(inbuf->addr));
      outbuf->port                              = UDP_SERVER_PORT;

      send_err                                  = netconn_send(g_udp_con, outbuf);

      if (send_err != ERR_OK)
      {
         debug_output_info("sendto error !!! \r\n");
      }
      else
      {
         debug_output_info("send byte %d : %s (%s) \r\n", buflen, buf, ipaddr_ntoa(&(outbuf->addr)));
      }

      netbuf_free(outbuf);
      netbuf_delete(outbuf);
      netbuf_delete(inbuf);
   }
}



