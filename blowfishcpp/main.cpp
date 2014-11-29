#include <openssl/blowfish.h>
#include <openssl/evp.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
using namespace std;

#define IP_SIZE 1024
#define OP_SIZE 1032

//unsigned char key[16];
//unsigned char iv[8];

int
sync (char *sync_file)
{
	std::string cp_cmd ("");
	std::string sync_cmd ("");
	std::string cp ("cp");
	std::string space (" ");
	std::string src (sync_file);
	std::cout << src << endl;
	std::string PATH ("/home/bala/S_drive/");
	std::string cd ("cd");
	std::string sep (" ; ");
	sync_cmd+=cd+space+PATH+sep+"./grive";
	cp_cmd+=cp+space+src+space+PATH;
	std::cout << cp_cmd.c_str() << endl;
	if(system(cp_cmd.c_str())==-1)
	{
		perror("system(3) failed");
	}
	else
	{
		std::cout << sync_cmd.c_str() << endl;
		if(system(sync_cmd.c_str())==-1)
			{
				perror("system(3) for sync failed");
			}
	}
	return 0;
}

int
print_key (char *key_file)
{
	unsigned char key[16];
	  ifstream myfile;
	  myfile.open (key_file,ios::in | ios::binary);
	  if (myfile.is_open())
	  {	int i=0;
		  while(i<16)//!myfile.eof())dint work coz it reads an extra char
		  {
			  myfile >> key[i];
			  printf ("%d=%d ",i,key[i]);
			  i++;
		  }
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

int
generate_key (char *key_file)
{
	unsigned char iv[8]={0};
//	basic_ofstream<unsigned char> file_stream;
//	file_stream.open(key_file,ios::out | ios::binary | ios::trunc);
//	if (!file_stream.is_open()) {
//	    cout << stderr << "Can't open output file !\n";
//	    exit(1);
//	}
//	else{

	  ofstream myfile;
	  myfile.open (key_file,ios::out | ios::binary | ios::trunc);


	  unsigned char key[16];
	int i, j, fd;
	if ((fd = open ("/dev/random", O_RDONLY)) == -1)
		perror ("open error");

	if ((read (fd, key, 16)) == -1)
		perror ("read key error");
//	file_stream.write((unsigned char *)key,sizeof(key));
	sleep(1);
	myfile << key;



	if ((read (fd, iv, 8)) == -1)
		perror ("read iv error");

	printf("128 bit key:\n");
	for (i = 0; i < 16; i++)
		printf ("%d \t", key[i]);
	printf("\nSize of key is %d",sizeof(key));
	printf ("\n ------ \n");


	printf("Initialization vector\n");
	for (i = 0; i < 8; i++)
		printf ("%d \t", iv[i]);

	printf ("\n ------ \n");
	close (fd);
	myfile.flush();
	sleep(1);
	myfile.close();



	exit(0);
	return 0;

}

int
decrypt (int infd, int outfd, int keyfd)
{
	unsigned char iv[8]={0};
	unsigned char key[16];
	unsigned char outbuf[IP_SIZE];
	int olen, tlen, n;
	char inbuff[OP_SIZE];

	int i=0;

		if(read(keyfd,key,16) == -1)
		{
			perror("key read failed");
			exit(1);
		}
		for(i=0;i<16;i++)
		{
		printf ("%d=%d ",i,key[i]);
	}
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init (&ctx);
	EVP_DecryptInit (&ctx, EVP_bf_cbc (), key, iv);

	for (;;)
	  {
		  bzero (&inbuff, OP_SIZE);
		  if ((n = read (infd, inbuff, OP_SIZE)) == -1)
		    {
			    perror ("read error");
			    break;
		    }
		  else if (n == 0)
			  break;

		  bzero (&outbuf, IP_SIZE);

		  if (EVP_DecryptUpdate (&ctx, outbuf, &olen, (const unsigned char*)inbuff, n) != 1)
		    {
			    printf ("error in decrypt update\n");
			    return 0;
		    }

		  if (EVP_DecryptFinal (&ctx, outbuf + olen, &tlen) != 1)
		    {
			    printf ("error in decrypt final\n");
			    return 0;
		    }
		  olen += tlen;
		  if ((n = write (outfd, outbuf, olen)) == -1)
			  perror ("write error");
	  }

	EVP_CIPHER_CTX_cleanup (&ctx);
	return 1;
}

int
encrypt (int infd, int outfd, int keyfd)
{
	unsigned char iv[8]={0};
	unsigned char key[16];
	unsigned char outbuf[OP_SIZE];
	int olen, tlen, n;
	char inbuff[IP_SIZE];

	int i=0;

		if(read(keyfd,key,16) == -1)
		{
			perror("key read failed");
			exit(1);
		}
		for(i=0;i<16;i++)
		{
		printf ("%d=%d ",i,key[i]);
	}
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init (&ctx);
	EVP_EncryptInit (&ctx, EVP_bf_cbc (), key, iv);

	for (;;)
	  {
		  bzero (&inbuff, IP_SIZE);

		  if ((n = read (infd, inbuff, IP_SIZE)) == -1)
		    {
			    perror ("read error");
			    break;
		    }
		  else if (n == 0)
			  break;

		  if (EVP_EncryptUpdate (&ctx, outbuf, &olen, (const unsigned char*)inbuff, n) != 1)
		    {
			    printf ("error in encrypt update\n");
			    return 0;
		    }

		  if (EVP_EncryptFinal (&ctx, outbuf + olen, &tlen) != 1)
		    {
			    printf ("error in encrypt final\n");
			    return 0;
		    }
		  olen += tlen;
		  if ((n = write (outfd, outbuf, olen)) == -1)
			  perror ("write error");
	  }
	EVP_CIPHER_CTX_cleanup (&ctx);
	return 1;
}

int
main (int argc, char *argv[])
{
	int flags1 = 0, flags2 = 0, outfd, infd, decfd, keyfd;
	mode_t mode;
	char choice, temp;
	int done = 0, n, olen;
	char key_file[31], sync_file[31];

//	bzero (&key, 16);
//	bzero (&iv, 8);
	bzero (&mode, sizeof (mode));

	flags1 = flags1 | O_RDONLY;
	flags2 = flags2 | O_RDONLY;
	flags2 = flags2 | O_WRONLY;
	flags2 = flags2 | O_CREAT;

	mode = mode | S_IRUSR;
	mode = mode | S_IWUSR;

	while (!done)
	  {
		  printf ("\nE - Encrypt a file\n");
		  printf ("D - Decrypt a file\n");
		  printf ("G - Generate a key\n");
		  printf ("P - Print a key from keyfile\n");
		  printf ("S - sync a file with S-Drive\n");
		  printf ("Q - Quit\n");

		  choice = getchar ();
		  temp = getchar ();

		  switch (choice)
		    {
		    case 'e':
		    case 'E':

		    	printf ("\nEnter Name of key file:\t");
		    	scanf("%30s",&key_file);
		    	if ((keyfd = open (key_file, flags1, mode)) == -1)
		    					    perror ("open key file error");

			    if ((infd = open (argv[1], flags1, mode)) == -1)
				    perror ("open input file1 error");

			    if ((outfd = open (argv[2], flags2, mode)) == -1)
				    perror ("open output file2 error");
			    printf("\ninfilefd=%d,outfilefd=%d,keyfilefd=%d\n",infd, outfd, keyfd );
			    encrypt (infd, outfd, keyfd);
			    close (keyfd);
			    close (infd);
			    close (outfd);
			    break;

		    case 'd':
		    case 'D':
		    	printf ("\nEnter Name of key file:\t");
		    			    	scanf("%30s",&key_file);
		    			    	if ((keyfd = open (key_file, flags1, mode)) == -1)
		    			    					    perror ("open key file error");


			    if ((outfd = open (argv[2], flags1, mode)) == -1)
				    perror ("open output file1 error");

			    if ((decfd = open (argv[3], flags2, mode)) == -1)
				    perror ("open output file2 error");
			    printf("\ninfilefd=%d,outfilefd=%d,keyfilefd=%d\n",infd, outfd, keyfd );


			    decrypt (outfd, decfd, keyfd);

			    close (outfd);
			    fsync (decfd);
			    close (decfd);
			    break;

		    case 'g':
		    case 'G':
		    	printf ("\nEnter Name of key file:\t");
		    	scanf("%30s",&key_file);
//		    	if ((keyfd = open (key_file, flags2, mode)) == -1)
//		    					    perror ("open key file error");
			    generate_key (key_file);
			    break;
		    case 'p' :
		    case 'P' :
		    	printf ("\nEnter Name of key file:\t");
		    			    	scanf("%30s",&key_file);
		    	//		    	if ((keyfd = open (key_file, flags2, mode)) == -1)
		    	//		    					    perror ("open key file error");
		    				    print_key(key_file);
		    				    break;
		    case 'S':
		    case 's':
		    	printf ("\nEnter Name of the file to be synced:\t");
		    	scanf("%30s",&sync_file);
		    	sync(sync_file);
			    break;
		    case 'Q':
		    case 'q':
		    	exit(0);
			    done = 1;
			    break;

		    default:
			    printf ("\nERROR: Unrecognized command. %c  Try again.\n",choice);
			    break;
		    }
	  }
	return 0;
}
