#include<stdio.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#include<errno.h>	//to know errors types while creating sockets
#include<unistd.h> 	//to close file descriptor

int main(  )
{
    char server_response[256];
    int my_socket,status;

    my_socket=socket(AF_INET,SOCK_STREAM,0);

if(my_socket==-1)
    {
    perror("socket");
    exit(1);
    }
else
    printf("socket descriptor value  %d\n",my_socket);

struct sockaddr_in server_address;

server_address.sin_family=AF_INET;
server_address.sin_port=htons(3333);
server_address.sin_addr.s_addr=INADDR_ANY; //any local ip address
printf("sin_addr.s_addr : %d\n", server_address.sin_addr.s_addr);
status=connect(my_socket, (struct sockaddr *) &server_address, sizeof(server_address));

if(status==-1){
    printf("there is an error with connect function\n");
    perror("socket");
close(my_socket);    
exit(1);
    }
else
    {printf("connect status= %d \n",status);

	recv(my_socket, &server_response, sizeof(server_response),0);

	printf("%s\n",server_response);
    }
close(my_socket);

return 0;
}
