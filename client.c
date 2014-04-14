#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
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
	char c = '0';
	printf("Enter '0' for Command execution, '1' for Program execution \n");
	write(sock,&c,1);
	
	if( c == '0' )
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
		printf("Done writing!\n");
		char c;
		while( read(sock,&c,1)!=0 )
		{
			printf("%c",c);
		}
		printf("\nDONE \n");
	}
	else
	{
		// Send the executable file
	}
}
