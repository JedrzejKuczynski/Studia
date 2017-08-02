#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFSIZE 10000

char *server = "127.0.0.1";	/* adres IP pętli zwrotnej */
short service_port = 1234;	/* port usługi daytime */

char buf[BUFSIZE];

int main ()
{

	struct sockaddr_in myaddr, serv_addr;

	// struktura adresu własnego
	/*memset(&myaddr, 0, sizeof(struct sockaddr_in));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = INADDR_ANY; // jakikolwiek adres
	myaddr.sin_port = htons(service_port);*/

	// struktura adresu serwera
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(service_port);

	int sock = socket (AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    int a = sizeof(struct sockaddr_in);

    size_t size = BUFSIZE;
	char* message = (char*)malloc(size * sizeof(char));
	printf("Zalogowanie na serwer: \"__login__ nazwa_uzytkownika\"\nWylogowanie: \"__logout__\"\nLista uzytkownikow: \"__show__\"\n");

    while(1){

    	if(strcmp(buf, "__exit__\n") == 0){
    		sendto(sock, buf, BUFSIZE, 0, (struct sockaddr*)&serv_addr, a);
			recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr*)&serv_addr, &a);
    		printf("%s", buf);
    		exit(0);
    	}

    	printf("\n> ");
		getline(&message, &size, stdin);
		strcpy(buf, message);
		sendto(sock, buf, BUFSIZE, 0, (struct sockaddr*)&serv_addr, a);
		recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr*)&serv_addr, &a);
    	printf("%s", buf);
	}

	close(sock);
	return(0);
}