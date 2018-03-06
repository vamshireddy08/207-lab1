/* server.c */
/* default ip: INADDR_ANY(localhost)	port number: 3000 */

#include<stdio.h>	//printf()
#include<sys/types.h>
#include<sys/socket.h>	// for socket(), bind(), listen(), accept()
#include<stdlib.h>	//atoi()
#include<netinet/in.h>
#include<errno.h>	// to check errors while using socket functions
#include<unistd.h>	//to close file descriptor
#include<arpa/inet.h>	//for sockaddr_in
#include <math.h>	//for sqrtf() function 
#include<string.h>
#include<stdbool.h>

/* function to check weather input is a valid number or not */
bool IsValidNumber(char * string)
{	int len= strlen(string);
	
for(int i = 1; i < len ; i ++)
  	 {	
	      if ( !((string[i] <='9' && string[i] >= '0' ) || string[i] == '.' ) ) 
	      	return 0;
  	 }
if (string[0] == '-' )
	return 1;
else if ( string[0] <='9' && string[0] >= '0' )
	return 1;
else 
	return 0; 
}

int main( int argc , char* argv[ ] ){
float errmsg1= -1 , errmsg2=  -2; 
char input[100];			//string to hold client input
int server_socket,client_socket;	//integers to hold client and server socket descriptor values
float val,x;
bool valid;

int portnumber=3000;	//default port number
if (argc==2)
{
	portnumber= atoi(argv[1]);
}else
{
printf(" usage: %s <portnumber> \n",argv[0]);
printf(" Enter Server Portnumber \n");
scanf("%d",&portnumber);
}

/* creating server socket */
server_socket=socket(AF_INET,SOCK_STREAM,0);	
if(server_socket==-1)
{
perror("socket");
exit(1);
}

/* filling server socket address structure */
struct sockaddr_in server_address,client_address;
 bzero(&server_address, sizeof(server_address));
 bzero(&client_address, sizeof(client_address));
socklen_t client_address_size = sizeof(client_address);

server_address.sin_family=AF_INET;
server_address.sin_port=htons(portnumber);
server_address.sin_addr.s_addr=htonl(INADDR_ANY);	//all ip address of local host machine

/* binding server socket to a port */
if (	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) < 0 )  
    {  
        perror("connect ");  
        return 1;  
    } 

/* listen to incomming connections at specified port */
 if( listen(server_socket,5) < 0 )	//no.of connections server can hold in queue is 5
	{
		perror("listen ");  
	        return 1; 
	}

while(1){
	
	client_socket=accept(server_socket,(struct sockaddr *) &client_address, &client_address_size);
	
	if(client_socket < 0)  
        {  
            perror("accept ");  
            continue;  
        } 

	recv(client_socket, &input, sizeof(input),0);	//receive input from client

	valid=IsValidNumber(input);		//to check weather user input is valid Number or not

	if (valid){
	x= atof(input);

		if(x < 0 )
		{
		send(client_socket,&errmsg1,sizeof(errmsg1),0);
		}
		else {
		val= sqrtf(x);		//standard function to calculate squareroot value
		send(client_socket,&val,sizeof(val),0);	// send squareroot value to client
		}
	}
	else
	{
	send(client_socket,&errmsg2,sizeof(errmsg2),0); //User input is not a number 
	}
	close(client_socket);
}

close(server_socket);	//close the socket connection, removes socket descriptor from table.
return 0;
}
