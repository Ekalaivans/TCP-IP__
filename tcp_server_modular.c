#include<stdio.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>

#define PORT 8080
#define Buffer_size 1024

// Controling functions

int server_socket_creation();
void address_configuration(struct sockaddr_in *address);
void socket_binding(int server_fd, struct sockaddr_in *address);
void listening_the_clients(int server_fd);
void client_handling(int server_fd);

int main()
   {
	   int server_fd;
	   struct sockaddr_in address;

	   //socket creation
	   server_fd = server_socket_creation();
	   address_configuration(&address);
	   socket_binding(server_fd, &address);
	   listening_the_clients(server_fd);

	   printf("server listening to the client...%d\n",PORT);

	   while(1)
	      {
		 client_handling(server_fd);
	      }
	    close(server_fd);
	    return 0;
   }

int server_socket_creation()
   {
	   int server_fd;
	   int opt = 1;

	   server_fd = socket(AF_INET, SOCK_STREAM, 0);
	   if(server_fd == -1)
	     { 
		perror("Socket creation failed...\n");
		exit(EXIT_FAILURE);
	     }
	    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	       {
		       perror("Setsockpot....failed...\n");
		       close(server_fd);
		       exit(EXIT_FAILURE);
	       }
	    return server_fd;

   }
void address_configuration(struct sockaddr_in *address)
  {
	  address->sin_family = AF_INET;
	  address->sin_addr.s_addr= INADDR_ANY;
	  address->sin_port = htons(PORT);
  }

void socket_binding(int server_fd, struct sockaddr_in *address)
  {
	  if(bind(server_fd,(struct sockaddr *)address,sizeof(*address))<0)
	  {
		  perror("socket..binding... failed..\n");
		  exit(EXIT_FAILURE);
	  }
  }

void listening_the_clients(int server_fd)
  {
	  if(listen(server_fd,5) < 0)
	    {
		  perror("Listening..failed..\n");
		  exit(EXIT_FAILURE);
	    }
  }

void client_handling(int server_fd)
  {
	  int new_socket;
	  char buffer[Buffer_size];
	  struct sockaddr_in client_address;
	  socklen_t addrlen = sizeof(client_address);
	  printf("Waiting for a client to connect..\n");


	  new_socket = accept(server_fd,(struct sockaddr *)&client_address, &addrlen);
	  if(new_socket < 0)
	     {
		     perror("Acceptance ....failed..\n");
		     return;
	     }
          int count;
	  int valread = read(new_socket, buffer, Buffer_size);
	  if(valread<0)
	       {
		  perror("Msg read failed..\n");
	       }
	    else
	       {
		       buffer[valread] ='\0';
		       printf("message has been recieved from the client...%d \n",count++);
	       }
	    close(new_socket);
  }
