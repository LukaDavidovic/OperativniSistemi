#define _DEFAULT_SOURCE//signal handler se vraca na podrazumevani
#define _XOPEN_SOURCE 700


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>

#define check_error(cond,msg)\
  do {\
    if (!(cond)) {\
      perror(msg);\
      fprintf(stderr, "File: %s\nFunction: %s\nLine: %d\n", __FILE__, __func__, __LINE__);\
      exit(EXIT_FAILURE);\
    }\
  } while (0)


int main(int argc,char** argv){

check_error(argc == 2,"nedovoljno elementa komandne linije\n");

//printf("PID = %jd\n",(intmax_t)argv[1]);

if(kill(4819,SIGKILL) != -1)
	printf("Proces postoji\n");
else
printf("Proces ne postoji.\n");

exit(EXIT_SUCCESS);
}
	
