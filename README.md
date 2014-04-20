Remote_Process_Invocation_POSIX
===============================

( USE SERVER, CLIENT FOLDERS for the latest commits )

Network application in which client can either send the program to execute on the server and get the result back or Client can remotely execute the command on the server and know the result of the command.

Server will do the processing of the input command and executes the command or compiles the C program accordingly.
Server will also execute the compiled C program and send the result back to the client

FILES:

file.c is the file the server is creating to store the incoming C program from the client
hello.c is the file which the client want to send it to the server to compile
a.out is the result of the compilation on the server.

server,client are executable files of the application
