#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<errno.h>// to check errors while using socket functions
#include<unistd.h>//to close file descriptor
int main(  ){
char msg[256]="you r connected to VAMSHI! ";
int server_socket,client_socket;

server_socket=socket(AF_INET,SOCK_STREAM,0);
if(server_socket==-1)
{
perror("socket");
exit(1);
}
else 
    printf("socket descriptor value %d\n",server_socket);

struct sockaddr_in server_address;
server_address.sin_family=AF_INET;
server_address.sin_port=htons(3333);
server_address.sin_addr.s_addr=INADDR_ANY;

bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

listen(server_socket,1);

client_socket=accept(server_socket,NULL,NULL);

send(client_socket,msg,256,0);

close(server_socket);

return 0;
}
