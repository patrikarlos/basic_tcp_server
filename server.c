/*
  Server, TCP, echo. 
  TCP server som hanterar en klient i __taget___. 
  Läser från klient, och echo tillbaka till klient. 

*/

#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>


/* Initializering */
int main(int argc, char *argv[]){

  int myPort=atoi(argv[1]);
  int myBacklogsize=5;
  
/* Kommunikation */

/* Skapa socket  (socket)*/
  
  int server_socket=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

  /* Koppla socket mot address och port (bind)*/ 
  struct sockaddr_in minAddress;
  memset(&minAddress,0, sizeof(minAddress));
  
  minAddress.sin_family=AF_INET;
  minAddress.sin_port=htons(myPort);
  inet_aton("0.0.0.0", &minAddress.sin_addr.s_addr);

  int rv = bind(server_socket, &minAddress, sizeof(minAddress));
  if (rv == -1 ) {
    perror("Problem, hjälp.");
    exit(1);
  }
  
  printf("Lyssnar på 0.0.0.0:%d \n", myPort);

  /* Tala om för OS att vi vill att den taremot anslutningar, å programmets vägnar (listen)*/
  rv = listen(server_socket, myBacklogsize);
  if (rv == -1) {
    perror("Problem, hjälp.");
    exit(1);
  }


  struct sockaddr_in derasAddress;
  socklen_t sin_size= sizeof(derasAddress);


  int klient_socket;
  char minBuffer[10000];
  int dL,sL;
  
  while(1) {
    
    klient_socket=accept(server_socket,&derasAddress, &sin_size );
    if ( klient_socket == -1 ) {
      perror("Accept");
      continue;
    }

    printf("Klient ansluten!!!\n");

    while(1){
      
      memset(&minBuffer,0,10000);
      dL=recv(klient_socket,&minBuffer, sizeof(minBuffer), NULL);
      if ( dL == -1 ){
	perror("Problem med klient.\n");
	break;
      } else if ( dL == 0 ) {
	printf(" fick 0 bytes. \n");
	break;
      } else {
	printf("%s|[%d]\n",minBuffer,dL);
      }
      if (dL>0) {
	sL=send(klient_socket,&minBuffer,dL,NULL);
	if (sL==-1) {
	  printf("-1 på send \n");
	  break;
	} else if (sL==0) {
	  printf("0 på send \n");
	  break;
	} else if (sL != dL ) {
	  printf("Skickade %d förväntade %d .\n", sL, dL);
	} else {
	  printf("Allt normalt.\n");
	}
      }
    }
    close(klient_socket);
    printf("Klient slut.\n");
    
  }
    
  
/* För varje klient (accept)=> ny socket!!  */ 
  /* För varje klient meddelande  */
  /* recv() => msg, kolla msg */ 
    /* Läs */
    /* Skicka svar (send) */
  /* Stäng ner klient, när klient är klar*/



/* clean up */
/* close(); */ 
}
