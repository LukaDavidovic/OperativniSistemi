#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	perror(msg);\
	exit(EXIT_FAILURE);\
	}\
	}while(0)

int main(int argc,char **argv){

check_error(argc == 4,"...");

int fd = open(argv[1],O_RDONLY);

if(fd == -1)
	check_error(0,"fd");

check_error(lseek(fd,atoi(argv[2]),SEEK_SET) != -1,"LSEEK");

int br = atoi(argv[3]);
char c;

while(br--){

	if(read(fd,&c,sizeof(c)) == 0)
		check_error(0,"read");
	lseek(fd,0,SEEK_CUR);
	write(1,&c,1);
}


exit(EXIT_SUCCESS);
}
