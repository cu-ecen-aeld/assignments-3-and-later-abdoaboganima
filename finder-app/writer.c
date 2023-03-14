#include <stdio.h>
#include <syslog.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


int main(int argc, char *argv[])
{
  if(argc!=3){
    fprintf(stderr, ANSI_COLOR_RED"The arguments are less than expected.. USAGE: ./writer filename str\n"ANSI_COLOR_RESET);
    openlog(NULL, 0, LOG_USER);
    syslog(LOG_ERR, "Invalid Number of arguments: %d", argc);
    return 1;
  }
  
  /*open the file for writing*/
  FILE *openFile = fopen(argv[1], "w");

  /*Handling if the file cannot be open*/
  if(openFile==NULL){
    fprintf(stderr, ANSI_COLOR_RED"The file %s cannot be open\n"ANSI_COLOR_RESET, argv[1]);
    syslog(LOG_ERR, "The file %s cannot be open", argv[1]);  
    fclose(openFile);
    return 1;
  }

  openlog(NULL, 0, LOG_USER);
  syslog(LOG_USER, "The file %s is open", argv[1]);  
  
  
  /*writing the string specified in the second argument over the file*/
  fwrite(argv[2], 1, strlen(argv[2]), openFile);


  fclose(openFile);
  syslog(LOG_INFO, "The file %s is closed", argv[1]);  
  
  
  return 0;
}
