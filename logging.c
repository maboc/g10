#include "logging.h"

void logger(char * logregel) {
  char * logfile;
  FILE * fp;
  time_t tijd;
  struct tm * tijd_break_down;
  char * totaal;

  tijd=time(NULL);
  tijd_break_down=localtime(&tijd);
  
  logfile=config_get_char("logfile");
  fp=fopen(logfile, "a");

  totaal=malloc(100);
  int tmp;
  tmp=sprintf(totaal, "%i/%i/%i %i:%i:%i : %s\n", tijd_break_down->tm_year+1900, tijd_break_down->tm_mon+1, tijd_break_down->tm_mday, tijd_break_down->tm_hour, tijd_break_down->tm_min, tijd_break_down->tm_sec, logregel);
    
  tmp=fprintf(fp, "%s", totaal);
  free(totaal);
  fclose(fp);
}
