#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#include <errno.h>
#define konverzija 1024.0

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	perror(msg);\
	exit(EXIT_FAILURE);\
	}\
	}while(0)

int main(int argc,char ** argv){

check_error(argc == 3,"...");

struct stat fInfo;



check_error(stat(argv[1],&fInfo) != -1,"...");

char ime1[1024],ime2[1024];

if(S_ISDIR(fInfo.st_mode))
{
	strcpy(ime1,strrchr(argv[1],'/'));
	strcpy(ime2,ime1+1);
}
else
	strcpy(ime2,argv[1]);

if(strcmp(argv[2],"KB") == 0)
{
	printf("%s %.0lfKB\n",ime2,ceil(fInfo.st_size/konverzija));
}
else if(strcmp(argv[2],"MB") == 0)
{
	printf("%s %.0lfMB\n",ime2,ceil(fInfo.st_size/konverzija/konverzija));
}
else if(strcmp(argv[2],"GB") == 0)
{
	printf("%s %.0lfGB\n",ime2,ceil(fInfo.st_size/konverzija/konverzija/konverzija));
}
else
	check_error(0,"netacan argument");

exit(EXIT_SUCCESS);
}
