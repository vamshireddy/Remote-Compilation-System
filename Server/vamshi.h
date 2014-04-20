#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

int Socket(int a)
{		
	int sock;
	if( a == 0 )
	{
		if( (sock = socket(AF_INET, SOCK_STREAM, 0))!=-1)
		{
			return sock;
		}
		else
		{
			perror("Error in socket\n");
			exit(0);
		}
	}
	else if( a == 1 )
	{
		if( (sock = socket(AF_INET, SOCK_DGRAM, 0))!=-1)
		{
			return sock;
		}
		else
		{
			perror("error in sock\n");
			exit(0);
		}
	}
}

void Bind(int sockfd,const struct sockaddr* myaddr,socklen_t len)
{
	if( bind(sockfd,myaddr,len)==-1)
	{
		perror("Error in bind ");
		exit(0);
	}
}

void Connect(int sockfd,const struct sockaddr* myaddr,socklen_t len)
{
	int a;
	if( ( a = connect(sockfd,myaddr,len) ) == -1 )
	{
		perror("Error in Connect : ");
		exit(0);
	}
	else
	{
		printf("Connected Succesfully\n");
	}
}

void Listen(int fd,int backlog)
{
	char* ptr;
	if( (ptr = getenv("LISTENQ"))!=NULL )
		backlog = atoi(ptr);
	if( listen(fd,backlog) < 0 )
	{
		perror("Error in Listen Call: ");
		exit(0);
	}
}

int Accept(int sock,struct sockaddr* client, socklen_t* len)
{
	int conn_sock;
	// If you dont want the client's protocol address , then put NULL, NULL in 2,3 args
	// It will return the client sock socket which is connected
	// It is closed each time through the loop
	if( (conn_sock = accept(sock,client,len)) == -1)
	{
		perror("Error in Accept : ");
		exit(0);
	}
	else
	{
		printf("Accepted connection\n");
		return conn_sock;
	}
}

int Sendto(int sock,const void* buffer,int len,int flags,const struct sockaddr* addr, int size)
{
	int no;
	if( (no = sendto(sock,buffer,len,flags,addr,size)) != -1)
	{
		return no;
	}
	else
	{
		perror("Error in sendto ");
		exit(0);
	}
}
int Recvfrom(int sock,void* buffer,int len,int flags,struct sockaddr* addr, int* size)
{
	int no;
	if( (no = recvfrom(sock,buffer,len,flags,addr,size)) != -1)
	{
		return no;
	}
	else
	{
		perror("Error in recvfrom ");
		exit(0);
	}
}
