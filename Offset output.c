#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_SIZE 1024

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	exit(EXIT_FAILURE);\
	}\
	}while(0)

int main(int argc,char **argv){

check_error(argc == 4,"...");

struct stat fInfo;

check_error(stat(argv[1],&fInfo) != -1,"stat");

if(S_ISREG(fInfo.st_mode))
	{
		int fd = open(argv[1],O_RDONLY,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		char buffer[MAX_SIZE];
		size_t size = atoi(argv[3])+ atoi(argv[2]);
		ssize_t n = read(fd,buffer,size);

		buffer[n]=0;

		
		if(n == -1)
			check_error(0,"");
	
		ssize_t n1 = write(1,(buffer + atoi(argv[2])),atoi(argv[3]));
		if(n1 == -1)
			check_error(0,"");
		
	}
else
	check_error(0,"not a regular file");



exit(EXIT_SUCCESS);
}
