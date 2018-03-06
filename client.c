/* client.c */
/* default ip: INADDR_ANY(localhost)	port number: 3000 */

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>

#include<sys/types.h>	//has socket datatypes
#include<sys/socket.h>
#include<netinet/in.h>

#include<errno.h>	//to know errors types while creating sockets
#include<unistd.h> 	//to close file descriptor

int main( int argc , char* argv[]  )
{
    float server_response;
    int my_socket,status;
    char input[100];

int portnumber=3000;	//default port number
if (argc==3)
{
	portnumber= atoi(argv[1]);
	bcopy(argv[2],input,98);
}
else if (argc==2){
	bcopy(argv[1],input,98);
}
else
{
printf(" usage: %s <portnumber> <number>\n",argv[0]);
printf(" Enter Server Portnumber \n");
scanf("%d",&portnumber);
printf(" please enter a number \n");
scanf("%s", input);
}
	
/* creating socket */
    my_socket=socket(AF_INET,SOCK_STREAM,0);

if(my_socket==-1)
    {
    perror(" error while creating socket");
    exit(1);
    }

/* filling socket address data structure */
	struct sockaddr_in server_address;

	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(portnumber);
	server_address.sin_addr.s_addr=htonl(INADDR_ANY); //any local ip address of local machine

/* connecting to server */
	status=connect(my_socket, (struct sockaddr *) &server_address, sizeof(server_address));

if(status==-1){
        perror("socket");
	close(my_socket);    
	exit(1);
    }
else
    {

	send(my_socket, &input,sizeof(input),0);		//sending number to server

	recv(my_socket, &server_response, sizeof(server_response),0);	//receiving response from the server
	if ( server_response == -1 )
	printf(" user input: %s \n This number is less than 0, No valid Squareroot \n",input);
	else if ( server_response == -2 )
	printf("user input: %s \n Not a valid Number \n", input );
	else
	printf(" user input: %s \n server response:  %f \n", input, server_response);	//printing server response to user
    }

/* closing the socket connection */
close(my_socket);

return 0;
}
