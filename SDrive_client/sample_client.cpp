#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<errno.h>
#include<netdb.h>
#include<sys/resource.h>

#include <fstream>

#include <openssl/blowfish.h>
#include <openssl/evp.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <iostream>
using namespace std;

int append_keynsend (char *key_file,char *buff);


int main()
{
	int sock,len,n=0,portno,bytesSent;
	struct sockaddr_in server ;
	struct hostent *server1;
	char filenameBuff[1024]="test";
	char buff[1024];
	char Keyfilename[100];
	fflush(stdout);

	if((sock=socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		printf("socket failed because a -1 was returned");
	}
	server.sin_family = AF_INET;
	server.sin_port = htons(3000);
	server1=gethostbyname("localhost");
	bzero(&server.sin_zero, 8);
	bcopy(server1->h_addr,&(server.sin_addr.s_addr),server1->h_length);
	if(connect(sock, (struct sockaddr *) &server,sizeof(server)) == -1)
	{
		printf("\nthe connection failed man \n");
	}
	bzero(buff,1024);
	strcat(buff,filenameBuff);
	strcat(buff,"$");
	printf("enter the key filename ");
	gets(Keyfilename);
	append_keynsend (Keyfilename,buff);
	if((send(sock, buff, strlen(buff) , 0))==-1)
	{
		printf("sending failed");
	}
}



int
append_keynsend (char *key_file,char *buff)
{
	unsigned char key[16];
	ifstream myfile;
	myfile.open (key_file,ios::in | ios::binary);
	if (myfile.is_open())
	{	int i=0;
	while(i<16)//!myfile.eof())dint work coz it reads an extra char
	{
		myfile >> key[i];
		//std::string cp_cmd key[i];
		//snprintf(buff,key[i]);

		//printf ("%d=%d ",i,key[i]);
		i++;
	}
	strcat(buff,(const char*)key);
	printf("the main buff is :%s\n\n",buff);
	}
	else
	{
		printf("\ncouldnt open key file !!");
		exit(1);
	}

	myfile.close();
	exit(0);
	return 0;
	//	}
}
