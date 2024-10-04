#define _XOPEN_SOURCE 700
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

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	perror(msg);\
	exit(EXIT_SUCCESS);\
	}\
	}while(0)
// ./5 dirA
// standardni izlaz:broj maxsize - minsize
int maksimum = 0;
int minimum=INT_MAX;

void sizeOfDir(char* putanja){

struct stat fInfo;
check_error(lstat(putanja,&fInfo)!=-1,"...");

if(!S_ISDIR(fInfo.st_mode)){

	if(S_ISREG(fInfo.st_mode)){

	if(maksimum < fInfo.st_size)
		maksimum = fInfo.st_size;
	if(minimum > fInfo.st_size)
		minimum = fInfo.st_size;

	}
	return;
	}

DIR* dir = opendir(putanja);
check_error(dir != NULL,"...");

struct dirent* dirEntry = NULL;
errno = 0;
while ((dirEntry = readdir(dir)) != NULL){

	char* path = malloc(strlen(putanja) + strlen(dirEntry->d_name) + 2);
	check_error(path != NULL,"...");

	strcpy(path,putanja);
	strcat(path,"/");
	strcat(path,dirEntry->d_name);

	if(!strcmp(dirEntry->d_name,".") || !strcmp(dirEntry->d_name,"..")){
	
	check_error(stat(path,&fInfo) != -1,"...");
		
	free(path);
	errno = 0;

	continue;	
	}
	sizeOfDir(path);
	free(path);
	errno = 0;

	}
	check_error(errno != EBADF,"readdir");
	check_error(closedir(dir) !=-1,"...");

	}

int main(int argc,char **argv){

if(argc !=2)
	return 1;

struct stat fInfo;
if(stat(argv[1],&fInfo) == -1)
	return 1;

if(!S_ISDIR(fInfo.st_mode))
	return 1;

sizeOfDir(argv[1]);

printf("%d\n",maksimum-minimum);

exit(EXIT_SUCCESS);
}
