#include "handler.h"

struct dll * results_free(struct dll * l){
  struct dll * tmp;
  
  if(l!=NULL){
    l=dll_first(l);
    while (l->next!=NULL){
      tmp=l->next;
      free(l);
      l=tmp;
    }
    free(l);
    l=NULL;
  }

  return l;
}

void write_prompt(int s){
  char * tmp;
  struct base_struct * active_base;

  tmp=malloc(10);
  bzero(tmp, 10);
  sprintf(tmp, "\r\n > ");
  write(s, tmp, strlen(tmp));

  free(tmp);
  
}

void * handler(void * sck){
  int s = *(int *) sck;
  int proceed =0;//0 - proceed 1 - stop proceeding (quit)
  char * inpbuf;
  struct dll * commands=NULL;
  struct base_struct * active_base=NULL;
  struct dll * results=NULL;
  
  output_line(s, "Welcome G10\r\n");

  write_prompt(s);
  
  while (proceed==0){
    inpbuf=malloc(1000);
    bzero(inpbuf,1000);
    read(s, inpbuf,1000);

    commands=parse(inpbuf);
    /********************************************************************************** 1 part commands */
    if (commands_count(commands)==1) {
      if (strncmp(commands_get_part(commands,1), "quit", strlen("quit"))==0){
	proceed=1;
      }
      if (strncmp(commands_get_part(commands,1), "shutdown", strlen("shutdown"))==0){
	proceed=1;
	goon=1;
      }
      /********************************************************************************** 2 part commands */
    } else if (commands_count(commands)==2) {
      /***********************************************************************************  bases list */
      if ((strncmp(commands_get_part(commands,1), "bases", 5)==0) && (strncmp(commands_get_part(commands,2), "list", 4)==0)){
	bases_list(s);
      } else if((strncmp(commands_get_part(commands,1), "use", 3)==0)){
	char * search;
	int isearch;

	search=malloc(strlen(commands_get_part(commands, 2))+1);
	bzero(search, strlen(commands_get_part(commands, 2))+1);
	search=strncpy(search, commands_get_part(commands, 2),strlen(commands_get_part(commands, 2)));

	isearch=atoi(search);

	active_base=bases_search_on_id(isearch);
 	if(active_base!=NULL) base_list(s, active_base);
	/********************************************************************************  node add */
      } else if (((strncmp(commands_get_part(commands, 1), "node", 4)==0)) && (strncmp(commands_get_part(commands, 2), "add", 3)==0)) {
	if(active_base!=NULL){
	  struct node_struct * n=NULL;
	  n=node_new(0);
	  active_base->nodes=dll_add(active_base->nodes, n);
	  node_display(s, n);
	    
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
	/*********************************************************************************  config list */
      } else if ((strncmp(commands_get_part(commands,1), "config", 6)==0) && (strncmp(commands_get_part(commands,2), "list", 4)==0)) {
	if (bases!=NULL){
	  struct base_struct * b;
	  b=bases_search_on_id(0);
	  base_display(s, b);
	}
	/*********************************************************************************  base display */
      } else if ((strncmp(commands_get_part(commands, 1), "base", 4)==0) && (strncmp(commands_get_part(commands, 2), "display", 7)==0)) {
	if (active_base!=NULL){
	  base_display(s, active_base);
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
	/*********************************************************************************  base new */
      } else if ((strncmp(commands_get_part(commands, 1), "base", 4)==0) && (strncmp(commands_get_part(commands, 2), "new", 3)==0)){
	struct base_struct * b;
	b=base_new(0);
	bases=dll_add(bases, b);
	base_display(s, b);
      }
      /********************************************************************************** 4 part commands */
    } else if (commands_count(commands)==4) {
      /************************************************************************************ node search */
      /************************************************************************************ node search swid */
      if ((strncmp(commands_get_part(commands,1), "node", 4)==0) &&
	  (strncmp(commands_get_part(commands,2), "search", 6)==0)) {
	if (active_base!=NULL) {
	  if (strncmp(commands_get_part(commands, 3), "swid", 4)==0) {
	    struct node_struct * node=NULL;
	    long int gezocht=0;

	    results=NULL;
	    gezocht=atoi(commands_get_part(commands, 4));
	    node=node_search_by_swid(active_base, gezocht);
	    if (node!=NULL) {
	      results=dll_add(results, node);
	    }
	  } else {
	    results=nodes_search(active_base->nodes, commands_get_part(commands,3), commands_get_part(commands,4));
	  }
	  if (results!=NULL) nodes_display(s, results);
	  results=results_free(results);
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
	/******************************************************************************** relation search */
      } else if ((strncmp(commands_get_part(commands,1), "relation", 8)==0) &&
		 (strncmp(commands_get_part(commands,2), "search", 5)==0)) {
	if (active_base!=NULL) {
	  results=NULL;
	  results=relations_search(active_base->nodes, commands_get_part(commands, 3), commands_get_part(commands, 4));

	  if (results!=NULL) nodes_display(s, results);
	  results=results_free(results);
	  
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
      }
      /********************************************************************************** 5 part commands */
    } else if (commands_count(commands)==5) {
      /********************************************************************************** node add relation */
      if ((strncmp(commands_get_part(commands, 1),"node", 4)==0) &&
	  (strncmp(commands_get_part(commands, 2), "add", 3)==0) &&
	  (strncmp(commands_get_part(commands, 3), "relation", 8)==0)){
	if (active_base!=NULL){
	  struct node_struct * n1=NULL, * n2=NULL;
	  struct relation_struct * r;
	  char * search;
	  int isearch;

	  search=malloc(strlen(commands_get_part(commands, 4))+1);
	  bzero(search, strlen(commands_get_part(commands, 4))+1);
	  search=strncpy(search, commands_get_part(commands, 4), strlen(commands_get_part(commands, 4)));

	  isearch=atoi(search);
	  n1=node_search_by_swid(active_base, isearch);
	  free(search);
	  
	  search=malloc(strlen(commands_get_part(commands, 5))+1);
	  bzero(search, strlen(commands_get_part(commands, 5))+1);
	  search=strncpy(search, commands_get_part(commands, 5), strlen(commands_get_part(commands, 5)));

	  isearch=atoi(search);
	  n2=node_search_by_swid(active_base, isearch);
	  free(search);
	  if((n1!=NULL) && (n2!=NULL)){
	    r=relation_new(0, n2);
	    n1->relations=dll_add(n1->relations, r);
	    node_display(s, n1);
	  }
	  
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
      } else if ((strncmp(commands_get_part(commands, 1), "base", 4)==0) &&
		 (strncmp(commands_get_part(commands, 2), "add", 3)==0) &&
		 (strncmp(commands_get_part(commands, 3), "attribute", 9)==0)){
	if (active_base!=NULL) {
	  struct attribute_struct * a;
	  a=attribute_new(0, commands_get_part(commands, 4), commands_get_part(commands,5));
	  active_base->attributes=dll_add(active_base->attributes, a);
	  base_list(s, active_base);
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
	
      }
      /********************************************************************************** 6 part commands */
      /******************************************************************************* node add attribute */
    } else if (commands_count(commands)==6) {
      if ((strncmp(commands_get_part(commands,1), "node", 4)==0) &&
	  (strncmp(commands_get_part(commands,2), "add", 6)==0) &&
	  (strncmp(commands_get_part(commands,3), "attribute", 9)==0)){
	if (active_base!=NULL){
	  struct node_struct * n;
	  struct attribute_struct * a;
	  char * search;
	  int isearch;

	  search=malloc(strlen(commands_get_part(commands, 4))+1);
	  bzero(search, strlen(commands_get_part(commands, 4))+1);
	  search=strncpy(search, commands_get_part(commands, 4),strlen(commands_get_part(commands, 4)));

	  isearch=atoi(search);

	  n=node_search_by_swid(active_base, isearch);
	  if(n!=NULL) { 
	    a=attribute_new(0, commands_get_part(commands, 5), commands_get_part(commands,6));
	    n->attributes=dll_add(n->attributes, a);
	    node_display(s, n);
	  }
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
	/************************************************************************ relation update relation */
      } else if ((strncmp(commands_get_part(commands, 1), "relation", 8)==0) &&
		 (strncmp(commands_get_part(commands, 2), "update", 6)==0) &&
		 (strncmp(commands_get_part(commands, 3), "relation", 8)==0)) {

	if (active_base!=NULL) {
	  struct node_struct * node=NULL, * relates_to_node=NULL;
	  struct relation_struct * relation=NULL;
	  long int node_swid, relation_swid, relates_to_node_swid;

	  node_swid=atoi(commands_get_part(commands, 4));
	  node=node_search_by_swid(active_base, node_swid);
	  if (node!=NULL) {
	    relation_swid=atoi(commands_get_part(commands,5));
	    relation=relation_search_by_swid(node, relation_swid);
	    if ( relation!=NULL) {
	      relates_to_node_swid=atoi(commands_get_part(commands, 6));
	      relates_to_node=node_search_by_swid(active_base, relates_to_node_swid);
	      if (relates_to_node!=NULL) {
		relation->node_to=relates_to_node;
		relation->control->dirty=1;
		relation->control->status=1;

		node_display(s, node);
	      }
	    }
	  }
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
	/*************************************************************************** base update attribute */
      } else if ((strncmp(commands_get_part(commands, 1), "base", 4)==0) &&
		 (strncmp(commands_get_part(commands, 2), "update", 6)==0) &&
		 (strncmp(commands_get_part(commands, 3), "attribute", 9)==0)) {
	if (active_base!=NULL){
	  struct attribute_struct * attribute;
	  long int attribute_swid=0;
	  
	  attribute_swid=atoi(commands_get_part(commands, 4));
	  attribute=attribute_search_by_swid(active_base->attributes, attribute_swid);
	  
	  free(attribute->key);
	  attribute->key=malloc(strlen(commands_get_part(commands, 5)+1));
	  bzero(attribute->key, strlen(commands_get_part(commands, 5)+1));
	  attribute->key=strncpy(attribute->key, commands_get_part(commands, 5), strlen(commands_get_part(commands, 5)));
	  free(attribute->value);
	  attribute->value=malloc(strlen(commands_get_part(commands, 6)+1));
	  bzero(attribute->value, strlen(commands_get_part(commands, 6)+1));
	  attribute->value=strncpy(attribute->value, commands_get_part(commands, 6), strlen(commands_get_part(commands, 6)));
	  attribute->control->status=1; // 0 - new (or nothing) 1 - update 2 - delete
	  attribute->control->dirty=1; // 0 - clean 1 - dirty
	  base_list(s, active_base);
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
      }
      /********************************************************************************** 7 part commands */
    } else if (commands_count(commands)==7){
      /*************************************************************************** relation add attribute */
      if ((strncmp(commands_get_part(commands,1), "relation", 4)==0) &&
	  (strncmp(commands_get_part(commands,2), "add", 6)==0) &&
	  (strncmp(commands_get_part(commands,3), "attribute", 9)==0)) {
	if (active_base!=NULL) {
	  struct node_struct * n;
	  struct attribute_struct * a;
	  struct relation_struct * r;
	  char * search;
	  int isearch;

	  search=malloc(strlen(commands_get_part(commands, 4))+1);
	  bzero(search, strlen(commands_get_part(commands, 4))+1);
	  search=strncpy(search, commands_get_part(commands, 4),strlen(commands_get_part(commands, 4)));

	  isearch=atoi(search);
	  free(search);
	  n=node_search_by_swid(active_base, isearch);
	  if (n!=NULL) {
	    search=malloc(strlen(commands_get_part(commands, 5))+1);
	    bzero(search, strlen(commands_get_part(commands, 5))+1);
	    search=strncpy(search, commands_get_part(commands, 5),strlen(commands_get_part(commands, 5)));
	    
	    isearch=atoi(search);
	    free(search);
	    r=relation_search_by_swid(n, isearch);
	    if (r!=NULL){
	      a=attribute_new(0, commands_get_part(commands, 6), commands_get_part(commands, 7));
	      r->attributes=dll_add(r->attributes, a);
	      node_display(s, n);	   
	    }
	  }
	  
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
      }
      /*********************************************************************************** node update attribute */
      else if ((strncmp(commands_get_part(commands,1), "node", 4)==0) &&
	       (strncmp(commands_get_part(commands,2), "update", 6)==0) &&
	       (strncmp(commands_get_part(commands,3), "attribute", 9)==0)) {
	if (active_base!=NULL) {
	  struct node_struct * node=NULL;
	  struct attribute_struct * attribute;
	  long int node_swid, attribute_swid;
	  int len;

	  node_swid=atoi(commands_get_part(commands, 4));
	  node=node_search_by_swid(active_base, node_swid);
	  if (node!=NULL) {
	    attribute_swid=atoi(commands_get_part(commands, 5));
	    attribute=attribute_search_by_swid(node->attributes, attribute_swid);
	    if (attribute!=NULL) {
	      free(attribute->key);
	      len=strlen(commands_get_part(commands, 6));
	      attribute->key=malloc(len+1);
	      bzero(attribute->key, len+1);
	      attribute->key=strncpy(attribute->key, commands_get_part(commands, 6), len);	    

	      free(attribute->value);
	      len=strlen(commands_get_part(commands, 7));
	      attribute->value=malloc(len+1);
	      bzero(attribute->value, len+1);
	      attribute->value=strncpy(attribute->value, commands_get_part(commands, 7), len);

	      attribute->control->dirty=1;
	      attribute->control->status=1; // 0 - new or nothing 1 - update 2 - delete

	      node_display(s, node);
	    }
	  }	
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	}
      }
      /********************************************************************************************** 8 part commands */
    } else if (commands_count(commands)==8) {
      /************************************************************************************ relation update attribute */
      if ((strncmp(commands_get_part(commands,1), "relation", 8)==0) &&
	       (strncmp(commands_get_part(commands,2), "update", 6)==0) &&
	       (strncmp(commands_get_part(commands,3), "attribute", 9)==0)) {
	struct node_struct * node=NULL;
	struct relation_struct * relation=NULL;
	struct attribute_struct * attribute=NULL;
	long int node_swid=0, relation_swid=0, attribute_swid=0;
	char * key, * value;
	long int len;
	
	node_swid=atoi(commands_get_part(commands, 4));
	if (active_base !=NULL) {
	  node=node_search_by_swid(active_base, node_swid);
	  if (node!=NULL) {
	    relation_swid=atoi(commands_get_part(commands, 5));
	    relation=relation_search_by_swid(node, relation_swid);
	    if (relation!=NULL) {
	      attribute_swid=atoi(commands_get_part(commands, 6));
	      attribute=attribute_search_by_swid(relation->attributes, attribute_swid);
	      if (attribute!=NULL) {
		free(attribute->key);
		len=strlen(commands_get_part(commands, 7));
		attribute->key=malloc(len+1);
		bzero(attribute->key, len+1);
		attribute->key=strncpy(attribute->key, commands_get_part(commands, 7), len);	    

		free(attribute->value);
		len=strlen(commands_get_part(commands, 8));
		attribute->value=malloc(len+1);
		bzero(attribute->value, len+1);
		attribute->value=strncpy(attribute->value, commands_get_part(commands, 8), len);

		attribute->control->dirty=1;
		attribute->control->status=1; // 0 - new or nothing 1 - update 2 - delete

		node_display(s, node);
	      }
	    }
	  }
	} else {
	  char * tmp_local;
	  tmp_local=malloc(100);
	  bzero(tmp_local, 100);
	  sprintf(tmp_local, "\n\nBase is not set\r\n");
	  write(s, tmp_local, strlen(tmp_local));
	  free(tmp_local);
	} 
      }
    }
    
    commands=commands_free(commands);
    write_prompt(s);
  }
  
  close(s);
  pthread_exit(NULL);
}

