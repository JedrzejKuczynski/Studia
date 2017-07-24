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
#define USERS 100

char buf[BUFSIZE];

struct user {

	char name[20];
	struct sockaddr_in address;
};

/*int user_check(char *user_names, char *name){

	int i = 0;
	for(i; i < sizeof(*user_names); i++){
		if(user_names[i] == *name)
			return 0;
	}
	return 1;
}*/

/*int addr_check(struct user *user_addr, struct in_addr client){

	int i = 0;

	for(i; i < sizeof(*user_addr); i++){
		if(user_addr[i].address.sin_addr.s_addr == client.s_addr){
			return 0;
		}
	}
	return 1;
}*/

int main(int argc, char* argv[]){

   struct sockaddr_in myaddr, other_addr;
   char *user_names[USERS];
   struct user *user_addr = (struct user*)malloc(USERS * sizeof(struct user*));
   int i = 0;

   /* address structure */
   memset(&myaddr, 0, sizeof(struct sockaddr_in));
   myaddr.sin_family = AF_INET;
   myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   myaddr.sin_port = htons(SERVER_PORT);

   /* create a socket */
   int sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

   /* bind a name to a socket */
   bind(sock, (struct sockaddr*)&myaddr, sizeof(struct sockaddr_in));

   while(1){
	   int a = sizeof(struct sockaddr_in);
	   recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr*)&other_addr, &a);
	   sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&other_addr, a);
    }

   close(sock);
   free(user_names);
   free(user_addr);
   return(0);
}