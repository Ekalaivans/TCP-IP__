#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

#define PORT 8080
#define Buffer_size 1024

int main()
  {
	  int server_fd,new_socket;
	  struct sockaddr_in address;
	  int adrlen = sizeof(address);
	  char buffer[Buffer_size];

	  // SOCKET CREATION...........................
	  server_fd = socket(AF_INET, SOCK_STREAM, 0);
	  if(server_fd == 0)
	  {
		  perror("Socket.... failed");
		  exit(EXIT_FAILURE);
	  }
	  //ADDRESS SETUP STRUCTURE CREATION.............

	  address.sin_family = AF_INET;
	  address.sin_addr.s_addr = INADDR_ANY;
	  address.sin_port = htons(PORT);

	  // socket binding..........

	  if(bind(server_fd,(struct sockaddr *)&address, sizeof(address)) < 0)
	     
		{
		   perror("Bind listening...failed");
		   exit(EXIT_FAILURE);
		   }
          //LISTEN FOR THE CLIENTS.............

           if(listen(server_fd,5) < 0)
	     {
	       perror(" Listening... failed");
	       close(server_fd);
	       exit(EXIT_FAILURE);
	       }

	     printf("Server listening to the port......%d.....\n",PORT);

      while(1)
	 {
	     printf("\n... N waiting for the another client to serve the message ...........\n");

		// ACEPTING THE CONNECTIONS.............

                new_socket = accept(server_fd,(struct sockaddr*)&address,(socklen_t *)&address);
                if(new_socket < 0)
	          {
                       perror("...Connection .....acceptance failed.........\n");
                        continue;
		  } // it performs skipping action of failed clients

             memset(buffer,0,Buffer_size);
             int valread = recv(new_socket, buffer , Buffer_size, 0);
             if(valread <= 0)
	       {
	          printf("Msg recived from the client is failed .....%s \n",buffer);
                  }
              else
	         {
	                printf(" MSG recieved from the client ....%s\n", buffer);
                 }
                     close(new_socket);
       }
       close(server_fd);
        return 0;
   }	

