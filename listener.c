#include "listener.h"


void * listener_start(void * data_in){
  int sckt;
  int ClientPort = 9999;
  struct sockaddr_in remote= {0};
  int sck;
  struct sockaddr_in clnt;
  int clnt_ln;
  char * s;
  
  sckt = socket(AF_INET, SOCK_STREAM,0);
  if (sckt == -1 ){
    printf("problems creating listening socket\r\n");
  } else {
    printf("Listening socket created\n");
    
    remote.sin_family = AF_INET; /* Internet address family */
    remote.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    remote.sin_port = htons(ClientPort); /* Local port */
    if(bind(sckt,(struct sockaddr *)&remote,sizeof(remote))!=0){
      printf("Socket binding did not succeed\n");
    } else {
      printf("Socket binding succeeded\r\n");
      
      /* Start listening on the socket */
      /* 10 is the numbber of connections in backlog */
      listen(sckt, 10);
      
      /* size of an incoming message (?) */
      clnt_ln = sizeof(struct sockaddr_in);
      
      while (goon==0){
	printf("in listening loop\r\n");
	
	/* if an connection arrives ....accept it */
	sck = accept(sckt, (struct sockaddr *) &clnt, (socklen_t*)&clnt_ln);
	/* sck is a file desciptor */
	
	s=malloc(100);
	sprintf(s, "Accepted a connection on socket %i\r\n", sck);
	printf("%s\r\n", s);
	free(s);
	
	pthread_t pt;
	int rc;
	rc=pthread_create(&pt, NULL, handler, &sck);
	
      }
      printf("Shutdown issued\r\n");
      close(sckt);            
    }
  }
}
