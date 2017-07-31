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
#define USERS_CAP 100
int users = 0;

char buf[BUFSIZE];

struct user {

	char* name;
	struct sockaddr_in address;
};

int user_check(char** user_names, char* name){

	int i = 0;
	for(i; i < users; i++){
		if(strcmp(user_names[i], name) == 0)
			return 0;
	}
	return 1;
}

int find_user(struct sockaddr_in client_address, struct user* user_addr){

	int i = 0;
	for(i; i < users; i++){
		if(client_address.sin_addr.s_addr == user_addr[i].address.sin_addr.s_addr){
			return i;
		}
	}
	return -1;
}

void delete_user(char** user_names, struct user* user_addr, int index){

	int i = index;
	for(i; i < users - 1; i++)
		user_names[i] = user_names[i+1];
	user_names[users-1] = "";

	int j = index;
	for(j; j < users - 1; j++)
		user_addr[j] = user_addr[j+1];
}

void show_users(char** user_names, char* buf){

	int i = 0;
	memset(buf, 0, sizeof(buf));
	strcpy(buf, "Uzytkownicy na serwerze: ");
	for(i; i < users; i++){
		strcat(buf, user_names[i]);
		strcat(buf, ", ");
	}
}

int main(int argc, char* argv[]){

   struct sockaddr_in myaddr, other_addr;
   char* user_names[USERS_CAP];

   for(int i = 0; i < USERS_CAP; i++)
   		user_names[i] = (char*)malloc(21 * sizeof(char));

   for(int i = 0; i < USERS_CAP; i++)
   		user_names[i] = "";

   struct user* user_addr = (struct user*)malloc(USERS_CAP * sizeof(struct user*));
   memset(user_addr, 0, sizeof(user_addr));
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

	   if(strncmp(buf, "__login__ ", 10) == 0){
	   	char* name = strdup(buf);
	   	name = name+10;
	   	name[strlen(name)-1] = '\0';
	   	if(user_check(user_names, name)){
	   		user_names[i] = name;
	   		struct user new_user;
	   		new_user.name = name;
	   		new_user.address = other_addr;
	   		user_addr[i] = new_user;
	   		printf("Dodawanie uzytkownika %s zakonczylo sie powodzeniem!\n", name);
	   		i++;
	   		users++;
	   		strcpy(buf, "Witamy na serwerze! Schemat wiadomosci: /nazwa_uzytkownika wiadomosc\n");
	   }else{
	   	strcpy(buf, "Nazwa zajeta!\n");
	   }
    }else if(strcmp(buf, "__logout__\n") == 0){
    	int index = find_user(other_addr, user_addr);
    	char* name = user_names[index];
    	delete_user(user_names, user_addr, index);
    	i--;
    	users--;
    	printf("Usuwanie uzytkownika %s z listy zakonczylo sie powodzeniem!\n", name);
    	strcpy(buf, "Dziekujemy za odwiedziny! Do zobaczenia!\n");
    }else if(strcmp(buf, "__show__\n") == 0){
    	show_users(user_names, buf);
    }

    sendto(sock, buf, sizeof(buf), 0, (struct sockaddr*)&other_addr, a);
}

   close(sock);
   memset(user_names, 0, sizeof(user_names));
   memset(user_addr, 0, sizeof(user_addr));
   free(user_names);
   free(user_addr);
   return(0);
}