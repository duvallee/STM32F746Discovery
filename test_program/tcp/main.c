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

#define TCP_SERVER_PORT                                  7810

int main(int argc, char* argv[])
{
   int client_socket;
   int port                                              = TCP_SERVER_PORT;

   struct sockaddr_in client_addr;

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


   client_socket                                         = socket(PF_INET, SOCK_STREAM, 0);
   if (client_socket < 0)
   {
      printf("cann't create socket : %s \r\n", strerror(errno));
      exit(1);
   }

   memset(&client_addr, 0, sizeof(client_addr));
   client_addr.sin_family                                = AF_INET;
   client_addr.sin_port                                  = htons(port);
   client_addr.sin_addr.s_addr                           = inet_addr(argv[1]);

   printf("TCP PORT  : %d(%d) \r\n", ntohs(client_addr.sin_port), port);
   printf("SERVER IP : %s \r\n", inet_ntoa(((struct sockaddr_in *) &client_addr)->sin_addr));

   if (connect(client_socket, (struct sockaddr*) &client_addr, sizeof(client_addr)) < 0)
   {
      printf( "Cann't connect server : %s \r\n", strerror(errno));
      exit(1);
   }

   sprintf(buff_snd, "send message : client -> server");
   read_write_byte                                       = write(client_socket, buff_snd, strlen(buff_snd) + 1);
   printf("send byte : %d \rn\n", read_write_byte);
   
   memset(buff_rcv, 0, sizeof(buff_rcv));
   read_write_byte                                       = -1;
   while (read_write_byte == -1)
   {
      read_write_byte                                    = read(client_socket, buff_rcv, sizeof(buff_rcv));
   }
   printf("%d:%s \r\n", read_write_byte, buff_rcv);
   close(client_socket);

   return 0;
}





