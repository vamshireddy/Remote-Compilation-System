Remote Process Invocation on UNIX server.
===============================

( Refer SERVER, CLIENT FOLDERS for the latest commits )

* An application in which a client can either send the program to execute on the server and can get the results back.
* Clients can also remotely execute the command on the server and get the results of the command.
* Server does the processing of the input command and executes the command or compiles the C program.

## Files
file.c is the file that is created by the server for storing the incoming program that is to be compiled.
hello.c is the file that is sent by the client to the server.
a.out is the result of the compilation on the server.
