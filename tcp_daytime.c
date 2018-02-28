#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include<arpa/inet.h>
#include<netdb.h>



	
int main(int argc, char **argv)
{
	int	sockfd, n, counter = 0;
	char	recvline[2048];
	struct sockaddr_in servaddr;
	
	if (argc != 3)
		 perror("usage: a.out <IPaddress/domain name> <port number/service type>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		 perror("error opening socket");

	

//	servaddr.sin_port= htons(atoi(arg[2])); 
// get port no. from service name daytime server
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13);	/* daytime server */

// bcopy((char *)server->h_addr,(char *)&servaddr.sin_addr.s_addr,server->h_length);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		 printf("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (struct sockaddr *)  &servaddr, sizeof(servaddr)) < 0)
		 perror("connect error"); 
	else 
	printf("connection established  %d \n",sockfd);

	 recv(sockfd, &recvline, 2047,0);
		
		printf("%s", recvline);
	
	
	return 0;
}
