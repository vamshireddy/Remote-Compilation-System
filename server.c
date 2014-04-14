#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>

#define MAX_LENGTH 15
#define MAX_COMMANDS 10
// This is the server where the client's program will be recieved and executed!

// The recieved file should be negotiated before

// 1. Can execute commands
// 2. Can execute executable

// Output should be directed to the client back!


struct command
{
	/* Command, No of args, args */
	char command[MAX_LENGTH];
	int no_args;
	char args[MAX_COMMANDS][MAX_LENGTH];
};

int main()
{
	/* Create a socket, an endpoint */
	int sock = socket(AF_INET,SOCK_STREAM,0);
	
	/* This simplifies the error checking */
	perror("After sock : ");

	/* Create the structre for assigning the IP and Port and pass it to kernel */

	struct sockaddr_in server;
	printf("Enter the port number : ");
	int port;
	scanf("%d",&port);
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	/* Now, the structure is initalized with all the parameters */

	// Bind it

	bind(sock,(struct sockaddr*)&server,sizeof(server));

	perror("After bind :");

	/* Now the socket has a name(port) and device has an IP */

	/* Make the socket as listening socket */

	listen(sock,10);

	/* Now this socket can accept the connections */

	for( ;; )
	{
		// Infinete loop
		struct sockaddr_in* client = (struct sockaddr_in*) malloc(sizeof(struct sockaddr_in));
		int len = sizeof(struct sockaddr_in);
		int client_sock = accept(sock,(struct sockaddr*)&client,&len);
		// Now the client has been accepted 

		// Serve the client

		/* Fork a new process */

		int process = fork();
		if( process == 0 )
		{
			// Child
			/* We dont need listening socket , so close it */
			close(sock);
			printf("Now ready to recieve from client!\n");
			char type;
			read(client_sock,&type,1);
			if( type == '0' )
			{
				printf("Ready for command\n");
				// Execute command 
				/* Now get the command name and parameters */
				/* Command will be in the structure */
				struct command cmd;
				uint8_t* byte_pointer = (uint8_t*)&cmd;
				/* Read the structure from the client and put it into the cmd var */
				read(client_sock,byte_pointer,sizeof(cmd));
				/* Now the structure is obtained */
				
				/* Create a pipe */
				int pipe_args[2];
				pipe(pipe_args);
				perror("pipe : ");
				/* Now fork a virtual process */
				int a;
				if( ( a = vfork() ) == 0 )
				{
					//CHILD
					close(pipe_args[0]);
					dup2(pipe_args[1],1);
					char* args[cmd.no_args];
				/* Since the array of string cmd.args is not a const string pointer array, we need to convert it*/
					int i;
					for(i=0;i<cmd.no_args;i++)
					{
						args[i] = cmd.args[i];
					}
					args[i] = NULL;
					// Now perform the execution
					if( execvp(cmd.command,args) == 0 )
					{
						printf("Error in execvp\n");
						exit(0);
					}
				}
				wait(a);
				close(pipe_args[1]);
				char c;
				while( read(pipe_args[0],&c,1)!=0)
				{
					write(client_sock,&c,1);
				}
				printf("Command %s has been executed succesfully\n",cmd.command);
				close(client_sock);
				close(pipe_args[0]);
			}
			else
			{
				// Execute the program 
			}
			exit(0);
		}
		// Parent
		/* We dont need the client_sock, it is handled by new process , so close it */
		close(client_sock);
	}
}
