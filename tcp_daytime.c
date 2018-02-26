#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include<arpa/inet.h>
#include<netdb.h>



	
int main(int argc, char **argv)
{
	int	sockfd, n, counter = 0;
	char	recvline[MAXLINE + 1];
	struct sockaddr_in servaddr;
struct hostent *server;

char buffer[256];

	if (argc != 2)
		err_quit("usage: a.out <IPaddress/domain name> <port number/service type>");

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		err_sys("error opening socket");
server=gethostname(argv[1]);
if (server==NULL)
{
	fprintf(stderr,"ERROR, no such host\n");
exit(0);
}
	bzero((char *)&servaddr, sizeof(servaddr));

//	servaddr.sin_port= htons(atoi(arg[2])); 
// get port no. from service name daytime server
	servaddr.sin_family = AF_INET;
	servaddr.sin_port   = htons(13);	/* daytime server */
// servaddr.sin_addr.s_addr=INADDR_ANY;
// bcopy((char *)server->h_addr,(char *)&servaddr.sin_addr.s_addr,server->h_length);
	if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		counter++;
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");

	printf("counter = %d\n", counter);
	exit(0);
}
