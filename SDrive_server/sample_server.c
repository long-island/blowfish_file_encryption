#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
#include<limits.h>
#include <mysql/mysql.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include "stdbool.h"
#include <sys/shm.h>
#include <string.h>
#include<pthread.h>

//#include <sys/signal.h>
//#include <sys/wait.h>
void* doSomeThing(int);

#define FILEPATH "/tmp/mmapped.bin"
#define NUMINTS  (1000)
//#define FILESIZE (NUMINTS * sizeof(int))
#define MAX_CONNECTIONS 100


void ParseTheBuff(char * buffer, int *sock_arr, int clientsd);

int SendMsgToClient(int clientsd,int *sock_arr,char * key,char *filename )
{
int i;
printf("the key is : %s",key);
printf("the filename is :%s",filename);
printf("\nCurrent clientSD is %d",clientsd);
for(i=0; i<=NUMINTS;i++)//INT_MAX
{

	if ((sock_arr[i]==1)&& i!=clientsd)
	{

		//send FIA (FIle Add) message to client
//<<<<<<< HEAD
		printf("\nCurrent clientSD is %d",clientsd);
		printf("\nSending message to clientSD %d",i);



                // if((send(i,buffer,50,0)) == -1)
		  //{
	            //printf("receive failed because a -1 was returned\n") ;
                  //}
//=======

		//printf("\nSending message to clientSD %i\n",i);

		int buff[50];
		bzero(buff,50);
		char MsgType[3]="FA";
		int ClientId = gethostid();
		char chString[100];

		snprintf(chString, sizeof(chString), "%d", ClientId);
		printf ("decimal: %s\n",chString);
		strcat(buff,"$");
		strcat(buff,chString);
		strcat(buff,"$");
		strcat(buff,"A");
		strcat(buff,"$");
		strcat(buff,MsgType);
		strcat(buff,"$");
		strcat(buff,filename);
		strcat(buff,"$");
		strcat(buff,key);
		strcat(buff,"$");

		printf("the buff is :%s\n\n",buff);

		if((send(i, buff, strlen(buff) , 0))==-1)
		{
		  printf("\nsending to %d failed",i);
		}






//>>>>>>> 7189a8f24f8980e4bfa9e108386fae0817b58aaf
	}
	else{
		//
	}
}

return 0;

}
//int clie;
//char buff[50];
int sock_arr[NUMINTS]={0};

int main()
{

	int sock,len,n,pid;
	//char buff[1024] ;
        int clie;
	//int i=0;
	int bytesSent;
	struct sockaddr_in server,client;
	//int N=INT_MAX;
	//int sock_arr[NUMINTS]={0};
	int reuse=1;
        pthread_t tid[3];

        //struct shared
        //{
          //int sock_arr[1024]
          //struct sockaddr_in clientStruct[1024]

        //} g_shar;

        //int shmID;
        //struct shared *shared_mem;


        //shmID = shmget(1009, sizeof( shar) , 0666 | IPC_CREAT);

        //shared_mem = shmat(shmID, NULL, 0);

        //memcpy(&evernota[0], &shar, sizeof(struct nota));
        //memcpy(&evernota[20],&shar,sizeof(struct nota));


        fflush(stdout);

	if((sock=socket(AF_INET,SOCK_STREAM,0)) == -1)
	{
		printf("socket creation failed since a -1 is returned\n");
		exit(-1);
	}
	if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int)) < 0)
	{
	    printf("setsockopt failed\n");
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
//	(void) signal(SIGCHLD, reaper);
        int i=0;
        int err;
	while(1)
	{
		if((clie = accept(sock, (struct sockaddr *) &client , &len) )== -1)
		{
			printf("accept failed\n");
			exit(-1);
		}

		sock_arr[clie]=1;
		//g_shar.sock_arr[clie]=1;
		//memcpy(g_shar.clientStruct[clie],&client,sizeof(client))
		//memcpy(shared_mem, &g_shar, sizeof(g_shar))
               // while(i < 3)
                   err = pthread_create(&(tid[i]), NULL, &doSomeThing, clie);
                   if (err != 0)
                   printf("\ncan't create thread :[%s]", strerror(err));
                   else
                   printf("\n Thread created successfully\n");
                   i++;
                          //}





		printf("\n clie=%d",clie);
		//mmap_map[clie+1]=1;//since the mmap is used from [1 to n]
		//fflush(mmap_map);

		printf("\nNew client ! FD=%d cli_sock=%d\n",clie, ntohs(client.sin_port));
		//pid=fork();
		//if(pid==0)
		//{

			//while(1)
			//{
			//	bzero(buff,50);
			//	if((recv(clie,buff,50,0)) == -1)
			//	{
			//		printf("receive failed because a -1 was returned\n");
			//	}
			//	else
			//	{
			//	ParseTheBuff(buff, shared_mem, clie, &server, len);
			//	}
				//close(clie);
				//exit(0);
			//}
		//}
		//else
		//{
			//sock_arr[clie]=0;
			//close(clie);
		//}
	}

	//exit(0);
}

void* doSomeThing(int clie_fd)
{
  //int clie_fd = *((int *)arg);
    while(1)
	{
	  char buff[1024];
	  bzero(buff,1024);
	  if((recv(clie_fd,buff,50,0)) == -1)
	    {
	      printf("receive failed because a -1 was returned\n");
            }
          else
	   {
	     ParseTheBuff(buff, sock_arr, clie_fd);
	   }
         }

}


void ParseTheBuff(char * buffer, int *sock_array, int clientsd)
{
	char *reqline[5];
	reqline[0] = strtok (buffer, "$");
	reqline[1] = strtok (NULL, "$");
	reqline[2] = strtok (NULL, "$");
	reqline[3] = strtok (NULL, "$");
	reqline[4] = strtok (NULL, "$");

	if(reqline[0]!=NULL){
	printf("the client id is :%s\n\n",reqline[0]);
	printf("the access group name is :%s\n\n",reqline[1]);
	printf("the Message type is :%s\n\n",reqline[2]);
	printf("the filename is :%s\n\n",reqline[3]);
	printf("the recd. key is :%s\n\n",reqline[4]);

	if (strcmp(reqline[2], "IN")==0)
	{
		return ;
		// add clientid and socket desc details to socket table
		//
	}
	else if(strcmp(reqline[2], "AD")==0)
	{

		// send message to other clients with info about the new file
		unsigned char key[100];
		int i=0;
		strcpy(key,reqline[4]);
		while(key[i]!='\0')
		{

			printf(" %d=%d ",i,key[i]);
			i++;
		}
	     printf("the buffer is : %s\n",buffer);
	     SendMsgToClient(clientsd,sock_array,reqline[4],reqline[3]);

	}
	else if(strcmp(reqline[2], "TE")==0)
	{
		//sock_arr[clie]=0;
		close(clientsd);
		exit(clientsd);
		// Remove client entry from socket table and close the corresponding SD

	}

	}
}




//Multi Process Server --
//#include<string.h>
//#include<stdio.h>
//#include<stdlib.h>
//#include<sys/socket.h>
//#include<sys/types.h>
//#include<netinet/in.h>
//#include<time.h>
//#include<limits.h>
//#include <mysql/mysql.h>
//#include <sys/fcntl.h>
//#include <sys/mman.h>
//#include <sys/stat.h>
//#include <unistd.h>
//#include "stdbool.h"
////#include <sys/signal.h>
////#include <sys/wait.h>
//
//#define FILEPATH "/tmp/mmapped.bin"
//#define NUMINTS  (1000)
//#define FILESIZE (NUMINTS * sizeof(int))
//#define MAX_CONNECTIONS 100
//
//
////reaper(int sig, int *sock_arr)
////{
////	int	status;
////
////	while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0){
////		sock_arr[status]=0;
////		printf("\nHi from Reaper, %d just died",status);
////	}
////		/* empty */
////
////}
//
//void ParseTheBuff(char * buffer, int *sock_arr, int clientsd, struct sockaddr_in *serv, int len);
//
//
////void LookupDb(char *AccessGrp);
//int SendMsgToClient(int clientsd,int *sock_arr,char * buffer, struct sockaddr_in *serv, int len)
//{
//	   	int mmap_i;
//	    int mmap_fd;
//	    int *mmap_map;  /* mmapped array of int's */
//
//	    mmap_fd = open(FILEPATH, O_RDONLY);
//	    if (mmap_fd == -1) {
//		perror("Error opening file for reading");
//		exit(EXIT_FAILURE);
//	    }
//
//	    mmap_map = mmap(0, FILESIZE, PROT_READ, MAP_SHARED, mmap_fd, 0);
//	    if (mmap_map == MAP_FAILED) {
//		close(mmap_fd);
//		perror("Error mmapping the file");
//		exit(EXIT_FAILURE);
//	    }
//
//	    /* Read the file int-by-int from the mmap
//	     */
//	    for (mmap_i = 1; mmap_i <=NUMINTS; ++mmap_i) {
//	    	sock_arr[mmap_i-1]=mmap_map[mmap_i];
//		//printf("%d: %d\n", mmap_i, mmap_map[mmap_i]);
//	    }
//
//
//
//	int i;
//	printf("\nCurrent clientSD is %d",clientsd);
//for(i=0; i<=NUMINTS;i++)//INT_MAX
//{
//
//	if ((sock_arr[i]==1)&& i!=clientsd)
//	{
//		if(((i, (struct sockaddr *)&serv, len)) == -1)
//		{
//			printf("\nBinding to sock %d failed\n",i);
//			exit(-1);
//		}
//		//send FIA (FIle Add) message to client
//
//		printf("\nSending message to clientSD %i\n",i);
//
//		int buff[50];
//		bzero(buff,50);
//		char MsgType[3]="FA";
//		int ClientId = gethostid();
//		char chString[100];
//
//		snprintf(chString, sizeof(chString), "%d", ClientId);
//		printf ("decimal: %s\n",chString);
//		strcat(buff,"$");
//		strcat(buff,chString);
//		strcat(buff,"$");
//		strcat(buff,"A");
//		strcat(buff,"$");
//		strcat(buff,MsgType);
//		strcat(buff,"$");
//		if((send(i, buff, strlen(buff) , 0))==-1)
//			{
//				printf("\nsending to %d failed",i);
//			}
//
//
//
//
//
//
//	}
//	else{
//		//
//	}
//}
//
//return 0;
//
//}
//int clie;
//
//
//
//int main()
//{
//	int mmap_i;
//	int mmap_fd;
//	int mmap_result;
//	int *mmap_map;  /* mmapped array of int's */
//	mmap_fd = open(FILEPATH, O_RDWR | O_CREAT | O_TRUNC, (mode_t)0600);
//	if (mmap_fd == -1)
//	{
//		perror("Error opening file for writing");
//		exit(EXIT_FAILURE);
//	}
//	mmap_result = lseek(mmap_fd, FILESIZE-1, SEEK_SET);
//	if (mmap_result == -1) {
//		close(mmap_fd);
//		perror("Error calling lseek() to 'stretch' the file");
//		exit(EXIT_FAILURE);
//	}
//	mmap_result = write(mmap_fd, "", 1);
//	if (mmap_result != 1) {
//		close(mmap_fd);
//		perror("Error writing last byte of the file");
//		exit(EXIT_FAILURE);
//	}
//	mmap_map = mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mmap_fd, 0);
//	if (mmap_map == MAP_FAILED) {
//		close(mmap_fd);
//		perror("Error mmapping the file");
//		exit(EXIT_FAILURE);
//	}
//
//
//	for (mmap_i = 1; mmap_i<=NUMINTS; ++mmap_i)
//	{
//		mmap_map[mmap_i] = 0;
//	}
//	//fflush(mmap_map);
//
//	//Procedure to remove shared memory follows
//	//    if (munmap(map, FILESIZE) == -1)
//	//    {
//	//	perror("Error un-mmapping the file");
//	//    }
//	//    close(fd);
//	//    return 0;
//
//	MYSQL *conn;
//	MYSQL_RES *res;
//	MYSQL_ROW row;
//	char *db_serv = "localhost";
//	char *user = "root";
//	char *password = "root"; /* set me first */
//	//char *database = "testdb";
//	conn = mysql_init(NULL);
//	/* Connect to database */
//	if (!mysql_real_connect(conn, db_serv,
//			user, password, NULL, 0, NULL, 0))
//	{
//		fprintf(stderr, "%s\n", mysql_error(conn));
//		exit(1);
//	}
//	else
//	{
//		printf("connection established");
//
//	}
//	//create database
//	if (mysql_query(conn, "CREATE DATABASE s_Drive"))
//	{
//		//printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
//		//return(1);
//	}
//	printf("database created");
//	//use database sDrive007
//	if (mysql_query(conn, "USE s_Drive") )
//	{
//		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
//		return(1);
//	}
//	printf("s_drive database");
//
//	//create tables
//	if(mysql_query(conn,"CREATE TABLE Socket_table (machine_id VARCHAR(4) PRIMARY KEY, socket_desc INT)"))
//	{
//		//printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
//
//	}
//	printf("table socket");
//	if(mysql_query(conn,"create table message_table(ac_group VARCHAR(1), machine_id VARCHAR(4) PRIMARY KEY,filename VARCHAR(31),filekey VARCHAR(16) )"))
//	{
//		//printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
//
//	}
//	printf("machine id table");
//
//
//	int sock,len,n,pid;
//	char buff[50] ;
//
//	int i=0;
//	int bytesSent;
//	struct sockaddr_in server,client;
//	int N=INT_MAX;
//	int sock_arr[NUMINTS]={0};
//	int reuse=1;
//	fflush(stdout);
//
//	if((sock=socket(AF_INET,SOCK_STREAM,0)) == -1)
//	{
//		printf("socket creation failed since a -1 is returned\n");
//		exit(-1);
//	}
//	if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&reuse,sizeof(int)) < 0)
//	{
//	    printf("setsockopt failed\n");
//	}
//	server.sin_family = AF_INET;
//	server.sin_port = htons(3000);
//	server.sin_addr.s_addr = INADDR_ANY;
//	bzero(&server.sin_zero, 8);
//	len = sizeof(server);
//
//	if((bind(sock, (struct sockaddr *)&server, len)) == -1)
//	{
//		printf("the binding process failed since a -1 is returned\n");
//		exit(-1);
//	}
//
//	if((listen(sock, 5)) == -1)
//	{
//		printf("listen failed\n");
//		exit(-1);
//	}
////	(void) signal(SIGCHLD, reaper);
//	while(1)
//	{
//		if((clie = accept(sock, (struct sockaddr *) &client , &len) )== -1)
//		{
//			printf("accept failed\n");
//			exit(-1);
//		}
//		sock_arr[clie]=1;
//		printf("\n clie=%d",clie);
//		mmap_map[clie+1]=1;//since the mmap is used from [1 to n]
//		//fflush(mmap_map);
//
//		printf("\nNew client ! FD=%d cli_sock=%d\n",clie, ntohs(client.sin_port));
//		pid=fork();
//		if(pid==0)
//		{
//
//			while(1)
//			{
//				bzero(buff,50);
//				if((recv(clie,buff,50,0)) == -1)
//				{
//					printf("receive failed because a -1 was returned\n");
//				}
//				else
//				{
//				ParseTheBuff(buff, sock_arr, clie, &server, len);
//				}
//				//close(clie);
//				//exit(0);
//			}
//		}
//		else
//		{
//			//sock_arr[clie]=0;
//			//close(clie);
//		}
//	}
//
//	exit(0);
//}
//
//
//
//
//void ParseTheBuff(char * buffer, int *sock_arr, int clientsd, struct sockaddr_in *serv, int len)
//{
//	char *reqline[5];
//	reqline[0] = strtok (buffer, "$");
//	reqline[1] = strtok (NULL, "$");
//	reqline[2] = strtok (NULL, "$");
//	reqline[3] = strtok (NULL, "$");
//	reqline[4] = strtok (NULL, "$");
//
//	if(reqline[0]!=NULL){
//	printf("the client id is :%s\n\n",reqline[0]);
//	printf("the access group name is :%s\n\n",reqline[1]);
//	printf("the Message type is :%s\n\n",reqline[2]);
//	printf("the filename is :%s\n\n",reqline[3]);
//	printf("the recd. key is :%s\n\n",reqline[4]);
//
//	if (strcmp(reqline[2], "IN")==0)
//	{
//		return ;
//		// add clientid and socket desc details to socket table
//		//
//	}
//	else if(strcmp(reqline[2], "AD")==0)
//	{
//
//		// send message to other clients with info about the new file
//		unsigned char key[100];
//		int i=0;
//		strcpy(key,reqline[4]);
//		while(key[i]!='\0')
//		{
//
//			printf(" %d=%d ",i,key[i]);
//			i++;
//		}
//		SendMsgToClient(clientsd,sock_arr,buffer, &serv, len);
//
//	}
//	else if(strcmp(reqline[2], "TE")==0)
//	{
//		//sock_arr[clie]=0;
//		close(clientsd);
//		exit(clientsd);
//		// Remove client entry from socket table and close the corresponding SD
//
//	}
//
//	}
//}
//
//
