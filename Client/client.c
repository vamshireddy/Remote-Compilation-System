#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<sys/types.h>
#include<fcntl.h>
#define MAX_LENGTH 15
#define MAX_COMMANDS 10
#define MAX_OUTPUT_LENGTH 500

struct command
{
	char command[MAX_LENGTH];
	int no_args;
	char args[MAX_COMMANDS][MAX_LENGTH];
};

int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	/* Now create the server structure */
	struct sockaddr_in server;

	char ip[10];
	int port;

	printf("Enter the IP address to connect : ");
	scanf("%s",ip);
	printf("Enter the port number : ");
	scanf("%d",&port);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET,ip,&server.sin_addr);

	/* Connect using the sever structure */

	if( connect(sock,(struct sockaddr*)&server,sizeof(server)) == -1 )
	{
		perror("");
		exit(0);
	}

	/* Tell, what service you want to server */
	char c[4];
	printf("Enter '0' for Command execution, '1' for C Program Compilation and execution \n");
	fflush(stdin);
	scanf("%s",c);
	/* Send the command choice */
	write(sock,&c,1);

	if( c[0] == '0' )
	{
		struct command cmd;
		printf("Enter the command to be executed without arguments : ( Ex. ping, traceroute, man, ls, mkdir ) ");
		scanf("%s",cmd.command);
		printf("How many arguments you want to give for the command typed above : ");
		scanf("%d",&cmd.no_args);
		int i=0;
		
		printf("Enter the arguments one by one : \n");

		/* This is mandatory for exec at server side */
		snprintf(cmd.args[0],MAX_LENGTH,"%s","Command-line");
		cmd.no_args++;
		
		for(i=1;i<cmd.no_args;i++)
		{
			scanf("%s",cmd.args[i]);
		}
		/* Done entering the commands */
		/* Send the stucture to the server */
		char* byte_pointer = (char*)&cmd;
		write(sock,byte_pointer,sizeof(struct command));
		/* Expecting the output */
		printf("The command has been sent succesfully \nWaiting for the result\n\n");		
	}
	else
	{
		// Send the executable file
		printf("Enter the file to be sent for execution : ");
		char file_name[MAX_LENGTH];
		scanf("%s",file_name);
		/* Use the file name and open the file for reading */
		int file = open(file_name,O_RDONLY,0777);
		if( file < 0 )
		{
			perror(" ");
			exit(0);
		}
		char c;
		while( read(file,&c,1) != 0 )
		{
			if( c == EOF )
			{
				printf("eof\n");
				write(sock,&c,1);
				break;
			}
			write(sock,&c,1);
		}
		c = EOF;
		write(sock,&c,1);
		printf("The file has been sent succesfully \nWaiting for the result\n");			
	}
	// Now read the result obtained from the server 
	char ch[200];
	int a;
	a = read(sock,&ch,200);
	printf("Got %d from server\n",a);
	if( a <=0 )
	{
		printf("Error in getting the output\n");
		exit(0);
	}
	printf("The output is %s\n",ch);
}
