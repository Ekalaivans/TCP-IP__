#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main()
     {
       int sock = 0;
       struct sockaddr_in serv_addr;
       char *msg = "Vanakkam da mapla Thuraiyur la irunthu ........";

		       
       sock = socket(AF_INET, SOCK_STREAM, 0);
       if (sock < 0)
       {
	perror("Socket creation error");
	return -1;
	 }

			     
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
         	{
		    perror("Invalid address / Address not supported");
		    return -1;
		}


	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
         	{
		    perror("Connection Failed");
		    return -1;
                }

	send(sock, msg, strlen(msg), 0);
        printf("Message sent\n");


	close(sock);

	return 0;
}

