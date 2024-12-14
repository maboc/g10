#include "listener.h"


void * listener_start(void * data_in){
  int sckt;
  int ClientPort = 9999;
  struct sockaddr_in remote= {0};
  int sck;
  struct sockaddr_in clnt;
  int clnt_ln;
  char * s;
  int option;
  char * tmp;

  tmp=malloc(100);
  bzero(tmp, 100);
  
  sprintf(tmp, "Starting Listener");
  logger(tmp);
  
  sckt = socket(AF_INET, SOCK_STREAM,0);
  if (sckt == -1 ){
    bzero(tmp, 100);
    sprintf(tmp, "problems creating listening socket");
    logger(tmp);
    
  } else {
    bzero(tmp, 100);
    sprintf(tmp, "Listening socket created");
    logger(tmp);
    
    setsockopt(sckt, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    
    
    remote.sin_family = AF_INET; /* Internet address family */
    remote.sin_addr.s_addr = htonl(INADDR_ANY); /* Any incoming interface */
    remote.sin_port = htons(ClientPort); /* Local port */
    if(bind(sckt,(struct sockaddr *)&remote,sizeof(remote))!=0){
      bzero(tmp, 100);
      sprintf(tmp, "Socket binding did not succeed");
      logger(tmp);
    } else {
      bzero(tmp, 100);
      sprintf(tmp, "Socket binding succeeded");
      logger(tmp);
      
      /* Start listening on the socket */
      /* 10 is the numbber of connections in backlog */
      listen(sckt, 10);
      
      /* size of an incoming message (?) */
      clnt_ln = sizeof(struct sockaddr_in);
      
      while (goon==0){
	bzero(tmp, 100);
	sprintf(tmp, "in listening loop");
	logger(tmp);
	
	/* if an connection arrives ....accept it */
	sck = accept(sckt, (struct sockaddr *) &clnt, (socklen_t*)&clnt_ln);
	/* sck is a file desciptor */

	bzero(tmp, 100);
	sprintf(tmp, "Accepted a connection on socket %i", sck);
	logger(tmp);
	
	pthread_t pt;
	int rc;
	rc=pthread_create(&pt, NULL, handler, &sck);
	
      }
      bzero(tmp, 100);
      sprintf(tmp, "Shutdown issued");
      logger(tmp);
      
      close(sckt);            
    }
  }
  free(tmp);
}
