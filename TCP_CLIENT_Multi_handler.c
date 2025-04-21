#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8080
#define Buffer_size 1024

int main()
    {
	 int sock = 0;
	 struct sockaddr_in serv_addr;
	 char *msg= " Vanakkam da mapla JDM seemaiyala irunthu........";

	//SOCKET CREATION..............
	while(1)
	{
	sock = socket(AF_INET,SOCK_STREAM, 0);
	if(sock < 0)
              {
		      perror("The Scoket creation is failed.....");
		      return -1;
	      }
	// SERVER SETUP 
	
        serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	 
	// Ip address to binary conversion 
	
	if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr) <=0)
	{
		perror("Address not valid....");
		return -1;
	}
	//Server connecting 
	
	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
         	
	     {
	       perror("Failed to connect.....\n");
               return -1;
	     }
	  //message sending to the server side 

	send(sock,msg,strlen(msg),0);
	printf("The has been sent to the server .....%s\n",msg);

	close(sock);
       }
	return 0;

    }



