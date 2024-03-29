
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void
main(void)
{
	int sock, cli;
	struct sockaddr_in server, client;
	unsigned int len;
	char mesg[] = "Hello world!\n";
	int sent;
	
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		perror("socket: ");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(10000);
	server.sin_addr.s_addr = INADDR_ANY; 
	bzero(&server.sin_zero, 0);	
	
	len = sizeof(struct sockaddr_in);
	if((bind(sock, (struct sockaddr *)&server, len) == -1))
	{
		perror("bind ");
		exit(-1);
	}

	if(listen(sock, 5) == -1)
	{
		perror("listen ");
		exit(-1);
	}

	while(1)
	{
		if((cli = accept(sock, (struct sockaddr*)&client, &len)) == -1)
		{
			perror("accept ");
			exit(-1);	
		}
		sent = send(cli, mesg, strlen(mesg), 0);
		printf("Sent %d bytes to client : %s\n", sent, inet_ntoa(client.sin_addr));
		close(cli);
	}
}
