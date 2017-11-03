/*
 *
 * File : main.c
 *
 * Copyright (c) 2017 duvallee
 *
 */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define UDP_SERVER_PORT                                  7811

int main(int argc, char* argv[])
{
   int udp_socket;
   int port                                              = UDP_SERVER_PORT;

   struct sockaddr_in bind_addr;
   struct sockaddr_in taget_addr;
   struct sockaddr_in receive_addr;
   socklen_t len;

   char buff_rcv[128];
   char buff_snd[128];
   int read_write_byte;

   if (argc != 2 && argc != 3)
   {
      printf("%s ipaddress port(7810) or %s ipaddress \r\n", argv[0], argv[0]);   
      return -1;
   }

   if (argc == 3)
   {
      port                                               = atoi(argv[2]);
   }


   udp_socket                                            = socket(PF_INET, SOCK_DGRAM , 0);
   if (udp_socket < 0)
   {
      printf("cann't create socket : %s \r\n", strerror(errno));
      exit(1);
   }

   // --------------------------------------------------------------------------
   memset(&bind_addr, 0, sizeof(bind_addr));
   bind_addr.sin_family                                  = AF_INET;
   bind_addr.sin_port                                    = htons(port);
   if (bind(udp_socket, (struct sockaddr *) &bind_addr, sizeof(bind_addr)) < 0)
   {
      printf("cann't bind : %s \r\n", strerror(errno));
      exit(1);
   }


   // --------------------------------------------------------------------------
   memset(&taget_addr, 0, sizeof(taget_addr));
   memset(&receive_addr, 0, sizeof(receive_addr));

   taget_addr.sin_family                                 = AF_INET;
   taget_addr.sin_port                                   = htons(port);
   taget_addr.sin_addr.s_addr                            = inet_addr(argv[1]);

   printf("UDP TARGET IP : %s (%d) \r\n", inet_ntoa(((struct sockaddr_in *) &taget_addr)->sin_addr), ntohs(taget_addr.sin_port));

   sprintf(buff_snd, "send udp message : hellow world !!!");
   read_write_byte                                       = sendto(udp_socket, buff_snd, strlen(buff_snd) + 1, 0, (struct sockaddr*) &taget_addr, sizeof(taget_addr));
   printf("send byte : %d \r\n", read_write_byte);
   
   memset(buff_rcv, 0, sizeof(buff_rcv));
   read_write_byte                                       = -1;

   len                                                   = sizeof(receive_addr);
   read_write_byte                                       = recvfrom(udp_socket, buff_rcv, sizeof(buff_rcv), 0, (struct sockaddr*) &receive_addr, &len);

   printf("received byte : %d (%s) \r\n", read_write_byte, buff_rcv);
   close(udp_socket);

   return 0;
}





