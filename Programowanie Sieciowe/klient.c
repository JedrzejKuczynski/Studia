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

char buf[BUFSIZE];

int main(int argc, char* argv[]){

	struct sockaddr_in serv_addr;

	if(argc < 3){
		printf("Podano za malo parametrow!\n");
		exit(0);
	}
	else if(argc > 3){
		printf("Podano za duzo parametrow\n");
		exit(0);
	}

	// struktura adresu serwera
	memset(&serv_addr, 0, sizeof(struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if(sock == -1){
		printf("Nie udalo sie utworzyc socketa!\n");
		exit(0);
	}

    int a = sizeof(struct sockaddr_in);

    size_t size = BUFSIZE;
	char* message = (char*)malloc(size * sizeof(char));
	printf("Zalogowanie na serwer: \"__login__ nazwa_uzytkownika\"\nWylogowanie: \"__logout__\"\nLista uzytkownikow: \"__show__\"\n\n");

	int forking = fork();

	if(forking == -1){
		printf("Blad podczas forka!\n");
		exit(0);
	}
	else if(forking == 0){
		while(1){
			recvfrom(sock, buf, BUFSIZE, 0, (struct sockaddr*)&serv_addr, &a);
			printf("\n%s\n", buf);
		}
	}else{
    	while(1){
			getline(&message, &size, stdin);
			strcpy(buf, message);
			sendto(sock, buf, BUFSIZE, 0, (struct sockaddr*)&serv_addr, a);
		}
	}

	close(sock);
	return(0);
}