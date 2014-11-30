#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>

void ParseTheBuff(char * buffer);

int clie;



int main( void)
{
	int sock,len,n,pid;
	char buff[1024] ;
	int bytesSent;
	struct sockaddr_in server,client;
	fflush(stdout);

	if((sock=socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		printf("socket creation failed since a -1 is returned\n");
		exit(-1);
	}

	server.sin_family = AF_INET;
	server.sin_port = htons(3000);
	server.sin_addr.s_addr = INADDR_ANY;
	bzero(&server.sin_zero, 8);
	len = sizeof(server);

	if((bind(sock, (struct sockaddr *)&server, len)) == -1)
	{
		printf("the binding process failed since a -1 is returned\n");
		exit(-1);
	}

	if((listen(sock, 5)) == -1)
	{
		printf("listen failed\n");
		exit(-1);
	}

	while(1)
	{
		if((clie = accept(sock, (struct sockaddr *) &client , &len) )== -1)
		{
			printf("accept failed\n");
			exit(-1);
		}

		pid=fork();
		if(pid==0)
		{
			//if((read(clie,buff,sizeof(buff),0)) == -1)
			//{
			//printf("reading failed because a -1 was returned\n");
			//}
			//printf(" The message sent by the client is : %s \n \n", buff);

			//TCPdaytimed(clie);
			bzero(buff,1024);
			if((recv(clie,buff,50,0)) == -1)
			{
				printf("receive failed because a -1 was returned\n");
			}

			ParseTheBuff(buff);
			close(clie);
			exit(0);
		}
		else
			close(clie);

	}

	exit(0);
}

void ParseTheBuff(char * buffer)
{
	char *reqline[3];
	reqline[0] = strtok (buffer, "$");
	if(strcmp(reqline[0],"Add")==0)
	{
		reqline[1] = strtok (NULL, " \t\n");
		reqline[2] = strtok (NULL, " \t\n");
	}
	else
	{
		if(strcmp(reqline[0],"Remove")==0)
		{
			reqline[1] = strtok (NULL, " \t\n");

		}

	}
	printf("the message type is :%s\n\n",reqline[0]);
	printf("the recd. key is :%s\n\n",reqline[1]);
	printf("the recd. filename is :%s\n\n",reqline[2]);

}



