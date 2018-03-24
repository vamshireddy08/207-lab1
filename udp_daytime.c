/* udp_daytime.c */

/* Libraries to support UDP Socket programming*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

	
int main(int argc, char **argv)
{
	/*      Arguments:      Server name or ip address - Name or address of the server that provides DAYTIME service	*/

	struct sockaddr_in servaddr;
	char	recvline[2048]="";
	int	sockfd, send_status,receive_status;
	unsigned int servlen;
	 struct hostent *server;                   	// pointer to host information entry 
    char *daytime_server = "test.rebex.net";  		//Default endpoint address(DAYTIME SERVER)
 
 	
/* creating a socket */
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{	perror(" cannot create socket ");
		exit(1);
	} 

/* getiing server ip and filling server address structure */

bzero( (char *) &servaddr, sizeof( servaddr ) );    //set all members of serveraddress to zeroes
	servaddr.sin_family = AF_INET;			// IPv4 address family
	servaddr.sin_port   = htons(13);		// Host to Network short
	//servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

 if( argc > 1 ) {                                	//Check if command lines aruments are given
        daytime_server = argv[ 1 ];                 	//Changes the server address to user input 
    }

server = gethostbyname( daytime_server );          
	if( server == NULL ) {
        perror( "gethostbyname failed" );
        exit( 1 );
    	}

 bcopy( (char *)server->h_addr, (char *)&servaddr.sin_addr.s_addr, server->h_length );

/* sending packet to server */	
if( send_status=sendto(sockfd," ",0,0, (struct sockaddr *)  &servaddr, sizeof(servaddr)) == -1)
{
perror( "sending datagram error" );
exit(1);
}

/* receiving packet from server */
if( (receive_status=recvfrom(sockfd, recvline, sizeof(recvline),0,(struct sockaddr*) &servaddr, (socklen_t*) &servlen ) ) == -1 )
{
perror("receive error\n");
exit(1);
}

printf("msg: %s\n",recvline);

	return 0;
}

