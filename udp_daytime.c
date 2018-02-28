#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include<unistd.h>

#include <netinet/ip.h>
#include<arpa/inet.h>
#include<netdb.h>



	
int main(int argc, char **argv)
{
	 struct hostent *server;                   // pointer to host information entry 
    char *daytime_server = "test.rebex.net";  //Default endpoint address(DAYTIME SERVER)
 server = gethostbyname( daytime_server );       
    if( server == NULL ) {
        perror( "gethostbyname failed" );
        exit( 1 );
    }

	struct sockaddr_in servaddr;
char	recvline[2048]=" ";
	int	sockfd, send_status,receive_status;
	char ip[]="132.239.1.6 ";
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		printf("error opening socket");
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13);
 bcopy( (char *)server->h_addr, 
            (char *)&servaddr.sin_addr.s_addr, server->h_length );

	
	
if( send_status=sendto(sockfd,"",0,0, (struct sockaddr *)  &servaddr, sizeof(servaddr)) == -1)
{
perror( "sending datagram" );
exit(1);
}


receive_status=recvfrom(sockfd, recvline, 2047,0,(struct sockaddr*) &servaddr,sizeof(servaddr));

printf("receive status %d  msg %s\n",receive_status, recvline);

	return 0;
}

