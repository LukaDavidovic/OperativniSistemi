#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <sys/wait.h>
#include <string.h>

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	perror(msg);\
	fprintf(stderr,"File: %s\nFunction: %s\nLine: %d\n",__FILE__,__func__,__LINE__);\
	exit(EXIT_FAILURE);\
	}\
	}while(0)

int main(int argc,char **argv){

check_error(argc == 3,"...");


check_error(execlp("mv","mv",argv[1],argv[2],NULL)!= -1,"exec failed");

exit(EXIT_SUCCESS);
}
