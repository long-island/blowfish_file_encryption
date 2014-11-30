#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>

void ParseTheBuff(char * buffer);
//int TCPdaytimed(int fd);
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
  else if 
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



/*int TCPdaytimed(int fd)
{

int i, n=0, a=0;
//char a;
char buff[100],buff1[100],buff2[100],buff3[100],buff4[100];
char *reqline[5];
char send1[1000];
char *pts; /* pointer to time string 
time_t now;  current time 
char *ctime();
(void) time(&now);
pts = ctime(&now);
reqline[0] = strtok (pts, " \t\n");
reqline[1] = strtok (NULL, " \t\n");
reqline[2] = strtok (NULL, " \t\n");
reqline[3] = strtok (NULL, " \t\n");
reqline[4] = strtok (NULL, " \t\n");

printf("\nthe field 1 is : %s \n", reqline[0]);
printf("\nthe field 2 is : %s \n", reqline[1]);
printf("\nthe field 3 is : %s \n", reqline[2]);
printf("\nthe field 4 is : %s \n", reqline[3]);
printf("\nthe field 5 is : %s \n", reqline[4]);
printf("\nthe 1 reqline[4] is %s",reqline[4]);
printf("\n the reqline1[1] is %s",reqline[1]);
printf("\n flush \n");

if(strcmp(reqline[1],"Jan") == 0)
{
    reqline[1]="1";
}
if(strcmp(reqline[1],"Feb") == 0)
{
    reqline[1]="2";
}
if(strcmp(reqline[1],"Mar") == 0)
{
    reqline[1]="3";
}
if(strcmp(reqline[1],"Apr") == 0)
{
    reqline[1]="4";
}
if(strcmp(reqline[1],"May") == 0)
{
    reqline[1]="5";
}
if(strcmp(reqline[1],"Jun") == 0)
{
    reqline[1]="6";
}
if(strcmp(reqline[1],"Jul") == 0)
{
    reqline[1]="7";
}
if(strcmp(reqline[1],"Aug") == 0)
{
    reqline[1]="8";
}
if(strcmp(reqline[1],"Sep") == 0)
{
    reqline[1]="9";
}
if(strcmp(reqline[1],"Oct") == 0)
{
    reqline[1]="10";
}
if(strcmp(reqline[1],"Nov") == 0)
{
    reqline[1]="11";
}
if(strcmp(reqline[1],"Dec") == 0)
{
    reqline[1]="12";
}

memset(send1,0,sizeof(send1));

strcat(send1,reqline[1]);
strcat(send1,"/");

strcat(send1,reqline[2]);
strcat(send1,"/");

//printf("\n the data1 is %s \n",send1);
printf("\n the 2 reqline[4] is %s \n",reqline[4]);
//strcat(reqline[4],"\0");

strcat(send1,reqline[4]);
strcat(send1," ");

//printf("\n the data1 is %s",send1);

strcat(send1,reqline[3]);
strcat(send1," ");
//printf("\nthe data1 is %s",send1);

strcat(send1,reqline[0]);

printf("\nsend1 is :%s\n",send1);


send(clie,send1,sizeof(send1),0);

//printf("\nbuff is :%s\n",buff);
return 0;
}*/




