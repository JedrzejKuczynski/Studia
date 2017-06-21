#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

#define SERVER_PORT 1234
#define BUFSIZE 10000

char buf[BUFSIZE];

int main(int argc, char* argv[])
{
   struct sockaddr_in myaddr, other_addr;

   /* address structure */
   memset(&myaddr, 0, sizeof(struct sockaddr_in));
   myaddr.sin_family = AF_INET;
   myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   myaddr.sin_port = htons(SERVER_PORT);

   /* create a socket */
   int sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

   /* bind a name to a socket */
   bind(sock, (struct sockaddr*)&myaddr, sizeof(struct sockaddr_in));

   while(1)
   {
	   int a = sizeof(struct sockaddr_in);
	   recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&other_addr, &a);
	   printf("\nJestem serwerem\n");
           time_t now;
           struct tm *local;
           time (&now);
           local = localtime(&now);
           sprintf(buf, asctime(local));
	   printf("Akcja powiodla sie!\n");
	   sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&other_addr, a);
       }

   close(sock);
   return(0);
}
