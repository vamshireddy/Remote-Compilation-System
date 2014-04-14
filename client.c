#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#define MAX_LENGTH 15
#define MAX_COMMANDS 10

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

	printf("Enter the port number : ");
	int port;
	scanf("%d",&port);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = INADDR_ANY;

	/* Connect using the sever structure */

	connect(sock,(struct sockaddr*)&server,sizeof(server));

	/* Tell, what service you want to server */
	char c[4];
	printf("Enter '0000' for Command execution, '1111' for Program execution \n");
	fflush(stdin);
	scanf("%s",c);
	write(sock,&c,1);
	if( c[0] == '0' )
	{
		struct command cmd;
		printf("Enter the command to be executed : ");
		scanf("%s",cmd.command);
		printf("How many args are there ");
		scanf("%d",&cmd.no_args);
		int i=0;
		
		printf("Enter the commands one by one\n");
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
		printf("The command has been sent succesfully \nWaiting for the result\n");		
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
				write(sock,&c,1);
				break;
			}
			write(sock,&c,1);
		}
		c = EOF;
		write(sock,&c,1);
		printf("The file has been sent succesfully \nWaiting for the result\n");			
	}
	char ch;
	while( read(sock,&ch,1)!=0 )
	{
		printf("%c",ch);
	}
	printf("\nDONE \n");
}
