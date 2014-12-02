#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<time.h>

#include <mysql/mysql.h>

void ParseTheBuff(char * buffer);
//void LookupDb(char *AccessGrp);
void SendMsgToClient(int clientfd,int i);
int clie;



int main( void)
{
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
	char buff[1024] ;
	int i=0;
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

	char *reqline[5];
	reqline[0] = strtok (buffer, "$");
	reqline[1] = strtok (NULL, "$");
	reqline[2] = strtok (NULL, "$");
	reqline[3] = strtok (NULL, "$");
	reqline[4] = strtok (NULL, "$");


	printf("the client id is :%s\n\n",reqline[0]);
	printf("the access group name is :%s\n\n",reqline[1]);
	printf("the Message type is :%s\n\n",reqline[2]);
	printf("the filename is :%s\n\n",reqline[3]);
	printf("the recd. key is :%s\n\n",reqline[4]);

if (strcmp(reqline[2], "IN")==0)
{
	// add clientid and socket desc details to socket table
	//
}
else if(strcmp(reqline[2], "AD")==0)
{
	// send message to other clients with info about the new file

}
else if(strcmp(reqline[2], "TE")==0)
{
	// Remove client entry from socket table and close the corresponding SD

}


	unsigned char key[100];
	int i=0;
	strcpy(key,reqline[4]);
    while(key[i]!='\0')
    {

    	printf("\c %d=%d ",i,key[i]);
        i++;
    }
}




