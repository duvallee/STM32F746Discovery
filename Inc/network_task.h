/*
 *
 * File : network_task.h
 *
 * Copyright (c) 2017 duvallee
 *
 */

#ifndef __NETWORK_TASK_H__
#define  __NETWORK_TASK_H__

#define TCP_SERVER_PORT                                  7810
#define UDP_SERVER_PORT                                  7811

void network_tcp_task(void const* argument);
void network_tcp_server_task(void const* argument);
void network_udp_server_task(void const* argument);

#endif      // __NETWORK_TASK_H__


