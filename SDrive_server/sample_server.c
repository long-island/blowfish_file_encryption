#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>
#include<limits.h>
#include <mysql/mysql.h>
//#include <sys/signal.h>
//#include <sys/wait.h>

#define MAX_CONNECTIONS 100


//reaper(int sig, int *sock_arr)
//{
//	int	status;
//
//	while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0){
//		sock_arr[status]=0;
//		printf("\nHi from Reaper, %d just died",status);
//	}
//		/* empty */
//
//}

void ParseTheBuff(char * buffer, int *sock_arr, int clientsd);


//void LookupDb(char *AccessGrp);
int SendMsgToClient(int clientsd,int *sock_arr,char * buffer)
{
	int i;
	printf("\nCurrent clientSD is %d",clientsd);
for(i=0; i<=32767;i++)//INT_MAX
{

	if ((sock_arr[i]==1)&& i!=clientsd)
	{
		//send FIA (FIle Add) message to client

		printf("\nSending message to clientSD %i\n",i);
	}
	else{
		//
	}
}

return 0;

}
int clie;



int main()
{
	printf("\nHI");
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *db_serv = "localhost";
	char *user = "root";
	char *password = "root"; /* set me first */
	//char *database = "testdb";
	conn = mysql_init(NULL);
	/* Connect to database */
	if (!mysql_real_connect(conn, db_serv,
			user, password, NULL, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	else
	{
		printf("connection established");

	}
	//create database
	if (mysql_query(conn, "CREATE DATABASE s_Drive"))
	{
		//printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		//return(1);
	}
	printf("database created");
	//use database sDrive007
	if (mysql_query(conn, "USE s_Drive") )
	{
		printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
		return(1);
	}
	printf("s_drive database");

	//create tables
	if(mysql_query(conn,"CREATE TABLE Socket_table (machine_id VARCHAR(4) PRIMARY KEY, socket_desc INT)"))
	{
		//printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));

	}
	printf("table socket");
	if(mysql_query(conn,"create table message_table(ac_group VARCHAR(1), machine_id VARCHAR(4) PRIMARY KEY,filename VARCHAR(31),filekey VARCHAR(16) )"))
	{
		//printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));

	}
	printf("machine id table");


	int sock,len,n,pid;
	char buff[50] ;

	int i=0;
	int bytesSent;
	struct sockaddr_in server,client;
	int N=INT_MAX;
	int sock_arr[32767]={0};
	int reuse=1;
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
	while(1)
	{
		if((clie = accept(sock, (struct sockaddr *) &client , &len) )== -1)
		{
			printf("accept failed\n");
			exit(-1);
		}
		sock_arr[clie]=1;
		printf("\nNew client ! FD=%d cli_sock=%d\n",clie, ntohs(client.sin_port));
		pid=fork();
		if(pid==0)
		{

			while(1)
			{
				bzero(buff,50);
				if((recv(clie,buff,50,0)) == -1)
				{
					printf("receive failed because a -1 was returned\n");
				}
				else
				{
				ParseTheBuff(buff, sock_arr, clie);
				}
				//close(clie);
				//exit(0);
			}
		}
		else
		{
			//sock_arr[clie]=0;
			//close(clie);
		}
	}

	exit(0);
}




void ParseTheBuff(char * buffer, int *sock_arr, int clientsd)
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
		SendMsgToClient(clientsd,sock_arr,buffer);

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


