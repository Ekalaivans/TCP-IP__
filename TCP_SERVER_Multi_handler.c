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
	  int opt =1,count=0;
	  struct sockaddr_in address;
	  int adrlen = sizeof(address);
	  char buffer[Buffer_size];

	  // SOCKET CREATION...........................
	//  server_fd = socket(AF_INET, SOCK_STREAM, 0);
	  if((server_fd = socket(AF_INET,SOCK_STREAM,0))==0)
	  {
		  perror("Socket..CREATION.. failed");
		  exit(EXIT_FAILURE);
	  }
	   
	  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt,sizeof(opt));


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
	       //close(server_fd);
	       exit(EXIT_FAILURE);
	    }

	   printf("Server listening to the port......%d.....\n",PORT);

          while(1)
           {
               printf("\n... waiting for the another client to connect......Client.no. %d \n",count++);

		// ACEPTING THE CONNECTIONS.............

               new_socket = accept(server_fd,(struct sockaddr*)&address,&adrlen);// if the client sends a message the server should perform this function to recieving after one by one when client sends 
                if(new_socket < 0)
	          {
                       perror("...Connection .....acceptance failed. || waiting for the next client........\n");
		       sleep(5);
                        continue;
		  } // it performs skipping action of failed clients

	               int valread = read(new_socket,buffer, Buffer_size);// server reads from the client 
                       buffer[valread]='\0';
                       printf("The nessage has been recieved fronm the client....%s\n",buffer);
	               close(new_socket);
	 }
                      close(server_fd);
                      return 0;

  }
