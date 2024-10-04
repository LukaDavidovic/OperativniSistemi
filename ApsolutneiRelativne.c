#define _XOPEN_SOURCE 700

// ./2 ../Documents b/c ./d/e

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	perror(msg);\
	exit(EXIT_FAILURE);\
	}\
	}while(0)

int duzinaApsolutne(char *path){

	char* apsolutna = realpath(path,NULL);
	
	if(apsolutna == NULL)
		check_error(0,"path");
	
	int n = strlen(apsolutna);
	free(apsolutna);
	return n;

}

void nemaPrivilegija(char *path){

struct stat fInfo;

check_error(stat(path,&fInfo)!= -1,"stat");

if(S_ISDIR(fInfo.st_mode)){

if((!(fInfo.st_mode & S_IROTH))&&(!(fInfo.st_mode & S_IWOTH))&&(!(fInfo.st_mode & S_IXOTH)))
{

printf("%d\n",duzinaApsolutne(path));

}
}
else
	check_error(0,"dir");


}

int main(int argc,char **argv){

check_error(argc >= 2,"argc");

int br = argc - 1;

for(int i=0;i<br;i++)
	nemaPrivilegija(argv[i+1]);


exit(EXIT_SUCCESS);
}













