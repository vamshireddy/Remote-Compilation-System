Remote_Process_Invocation_POSIX
===============================

Network application in which client can either send the program to execute on the server and get the result back or Client can remotely execute the command on the server and know the result of the command. This is not SSH.


In the client side the application will ask client to enter either of the two choices
1) Execute the command on the server and get back the result
2) Compile the C program which is sent and get the executed output back

Server will do the processing of the input command and executes the command or compiles the C program accordingly.
Serve will also execute the compiled C program and send the result back to the client

Error Handling:
TO BE FIXED : If the compiled program is wrong, The client gets infinete garbage printed on the screen

FILES:

file.c is the file the server is creating to store the incoming C program from the client
hello.c is the file which the client want to send it to the server to compile
a.out is the result of the compilation on the server.

server,client are executable files of the application
