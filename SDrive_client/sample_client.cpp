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
#include <strings.h>
using namespace std;

int print_key (char *key_file,char *buff);


int main(int argc , char *argv[])
{
int sock,len,n=0,portno,bytesSent;
//int n = 0;
struct sockaddr_in server ;
struct hostent *server1;
//char msg[100],buff[500],buff1[100],buff2[100],buff3[100],buff4[100];
//typedef enum {Add,Remove} MsgType;
//struct rusage servusage = {0};
//char MsgType[100];
//char keyBuff[1024];
char filenameBuff[1024]="test";
char buff[1024];  
char Keyfilename[100];
fflush(stdout);

if(argc !=3)
 {
 printf("please enter 3 values only");
 }

//portno=atoi(argv[2]);


if((sock=socket(AF_INET, SOCK_STREAM, 0)) == -1)
 {
   printf("socket failed because a -1 was returned");
 }


//if(server1 == NULL)
 //{
  //perror("server not found \n");
 //}

// hp = gethostbyname(argv[1]);
 //if(server == NULL);
// {
  // perror("no such host \n ");
 //}

  server.sin_family = AF_INET;
  server.sin_port = htons(3000);
  server1=gethostbyname(argv[1]);
  bzero(&server.sin_zero, 8);
  
  //bzero((char *) &server,sizeof(server));
  //server.sin_family = AF_INET;
  //bcopy((char *)server1->h_addr,(char *)&server.sin_addr.s_addr,server1->h_length);
   bcopy(server1->h_addr,&(server.sin_addr.s_addr),server1->h_length);
  //server.sin_port = htons(portno);


if(connect(sock, (struct sockaddr *) &server,sizeof(server)) == -1)
 {
   printf("\nthe connection failed man \n");
 } 
  
  //printf("please enter the message u want to send to the server: \n \n"); 
  

  bzero(buff,1024);
  //fgets(msg,100,stdin);
  
  //strcat(buff,key);
  
  strcat(buff,filenameBuff);
  strcat(buff,"$");
  printf("enter the key filename ");
  gets(Keyfilename);
  print_key (Keyfilename,buff);
  
  //printf("the buffer is : %s\n\n",buff);
  //bytesSent = send(sock, buff, strlen(buff) , 0);
  //printf("Numberof Bytes sent = %d \n \n", bytesSent);
  
   //bzero(buff,sizeof(buff));
   if((send(sock, buff, strlen(buff) , 0))==-1)
{
   printf("sending failed"); 
      
}

}



int
print_key (char *key_file,char *buff)
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
			  strcat(buff,key[i]);
			  //printf ("%d=%d ",i,key[i]);
			  i++;
		  }
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

   //bzero(buff1,sizeof(buff));
   //bzero(buff2,sizeof(buff));
   //bzero(buff3,sizeof(buff));
   //bzero(buff4,sizeof(buff));
   
  /*if((n = recv(sock,buff,sizeof(buff),0)) == -1)
   {
    printf("reading failed because a -1 was returned");
   }

  printf("the time string recd is : %s\n ",buff);

}

//printf("the data recdis : %s \n",buff);


/*if((n = recv(sock,msg ,100,0)) == -1)
   {
    printf("reading failed because a -1 was returned");
   }

printf("message from server is : %s \n \n \n",msg);
printf("bytes read  : %d \n \n \n",n);*/


//servusage = EmptyStruct;
/*if((recv(sock,(struct rusage*)&servusage, sizeof(servusage),0)) == -1)
   {
    printf("reading failed because a -1 was returned");
   }

printf("here are the GETRUSAGE DETAILS : \n\n");
printf("the maximum resident size is : %ld \n \n ",servusage.ru_maxrss);
printf("the integral shared memory size is : %ld \n \n",servusage.ru_oublock);


}*/

