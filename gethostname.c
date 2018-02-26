#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <errno.h>
#include <netdb.h> 
#include <arpa/inet.h>

#define h_addr h_addr_list[0]

void bin(unsigned n){

	if(n>1)
	bin(n/2);

printf("%d",n%2);
}

int get_ip(char *  , char *);




int main(int argc , char *argv[])

{	char str[INET_ADDRSTRLEN];	
uint8_t binary[4];	int i=0;
	struct in_addr test,localInterface;
	if(argc!=3){
    		printf(" usage: %s server domain_name/seerver ip , server port_number\n", argv[0]);
    		exit(-1); 
    		}
    else{
    	for(i=0;i<argc;i++)
    	printf("arg %s \t",argv[i]);  
    } 


   
    char *hostname = argv[1];     
    char ip[100];     
    get_ip(hostname , ip);     
    printf("%s resolved to %s\n" , hostname , ip);
  
   if(inet_pton(AF_INET, ip,&(test.s_addr)))
	{ memcpy(binary,&test.s_addr,4);
printf("binary value: %u\n",binary);
 bin(test.s_addr);
	printf("\n");
printf("inet_pton value: %d\n", test.s_addr);  

inet_ntop(AF_INET, &(test.s_addr),str,INET_ADDRSTRLEN);
printf("ip value: %s\n",str);

}
localInterface.s_addr = inet_addr(ip);
printf("inet_addr value : %d\n", localInterface.s_addr);



return 0;
} 




int get_ip(char * hostname , char* ip) 
{  struct hostent *he;     
   struct in_addr **addr_list;     
   int i;     
   if ( (he = gethostbyname( hostname ) ) == NULL)     
   { herror("gethostbyname");         
     return 1;
   }
	else
	{
	printf("Name: %s \n",he->h_name);
	printf("address type: %d\n",he->h_addrtype);
	printf("address length: %d\n",he->h_length);
		printf("%u\n",inet_addr(he->h_addr));
	}
     
   addr_list = (struct in_addr **) he->h_addr_list;
    for(i = 0; addr_list[i] != NULL; i++)
    {   strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;}

    return 1;
}

