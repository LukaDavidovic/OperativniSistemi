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

struct stat fInfo;

check_error(stat(argv[1],&fInfo) != -1,"stat");

char *ime;
char imedodatka[1024];

if(!(S_ISDIR(fInfo.st_mode)))
	check_error(0,"...");

ime = strrchr(argv[1],'/');

if(ime != NULL){
printf("%s\n",ime);

int i;

for(i=0;i<strlen(argv[1]) - strlen(ime);i++)
	imedodatka[i] = argv[1][i];

int j=0;

imedodatka[i] = '/';

i++;

printf("%s\n",imedodatka);

for(;i< strlen(argv[1]) + strlen(argv[2]);i++)
	{imedodatka[i] = argv[2][j];j++;}

imedodatka[i+1] = 0;
printf("%s\n",imedodatka);
}
else
strcpy(imedodatka,argv[2]);



check_error(execlp("mv","mv",argv[1],imedodatka,NULL)!= -1,"exec");

exit(EXIT_SUCCESS);
}
