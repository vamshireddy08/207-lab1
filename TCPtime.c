/* TCPtime.c - TCPtime */

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <stdio.h>
#include <time.h>
#include "errexit.c"
#include "connectsock.c"
#include "connectTCP.c"


#define UNIXEPOCH 2208988800 /* UNIX epoch, in UCT secs */

int errexit(const char *format, ...);
int connectTCP(const char *host, const char *service);

int getTime(const char *host, const char *port) {
	int socket;
	int n; // read count
    time_t now;

    socket = connectTCP(host, port);

    // Read the time
    n = recv(socket, (char *)&now, sizeof(now),0);
    if (n < 0) {
        errexit("read failed: %s\n", strerror(errno));
    }
    now = ntohl((u_long)now);
    now -= UNIXEPOCH; // convert UCT to UNIX epoch

    printf("%s: %s", host, ctime(&now));

    return (int)now;
}

int main(int argc, char *argv[]) {
	char server1[256];
    char port37[3]="37";	//well known port for TIME service
    char server2[256];
        
    printf("Please enter time server1's address: ");
    scanf("%s", server1);
    

    printf("Please enter time server2's  address: ");
    scanf("%s", server2);
    
    int time1 = getTime(server1,port37);   
    int time2 = getTime(server2,port37);

    printf("Time difference is %d\n", time2 - time1);
    exit(0);
}
