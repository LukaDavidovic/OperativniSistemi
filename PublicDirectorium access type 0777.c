#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <stdbool.h>


#define check_error(cond,userMsg)\
	do{ \
	if(!(cond)){\
		perror(userMsg);\
		exit(EXIT_FAILURE);\
		}\
	}while(0)

int main(int argc,char** argv){

check_error(argc == 2,"");

mode_t oldUmask = umask(0);

oldUmask = 0;

long mode = strtol("0777",NULL,8);

int fd = mkdir(argv[1],mode);

if(fd == -1){

	if(errno == EEXIST){

		exit(EXIT_FAILURE);
	}
	
	else{

		check_error(false,"file open failed");		
	
	}

}
else{
	close(fd);
}

umask(oldUmask);

close(fd);
exit(EXIT_SUCCESS);
}
