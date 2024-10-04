#define _XOPEN_SOURCE 700




#include <stdlib.h>
#include <stdbool.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE 1024

#define check_error(cond,msg)\
	do{\
	if(!(cond))\
	exit(EXIT_FAILURE);\
	}while(0)

bool os_file_open(const char *fpath,const char *mode,int *fd){

static mode_t defaultMode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

int flags = 0;

if(mode[0]=='-' && mode[1] == 'r'){

	flags |= O_RDONLY;

	*fd = open(fpath,flags,defaultMode);

	char buffer[MAX_SIZE];
	size_t nbytes = sizeof(buffer);
	ssize_t bytes_read;

	bytes_read = read(*fd,buffer,nbytes);
	


	if(bytes_read == -1)
		check_error(false,"");	



	nbytes = strlen(buffer);

	if(write(1,buffer,nbytes) == -1)
		check_error(false,"");
	



}
else if(mode[0] == '-' && mode[1] == 'w'){

	flags |= O_WRONLY;
	flags |= O_TRUNC;
	flags |= O_CREAT;
	*fd = open(fpath,flags,defaultMode);

	char buffer[MAX_SIZE];
	size_t nbytes = sizeof(buffer);
	ssize_t bytes_read;

	bytes_read = read(0,buffer,nbytes);
	
	buffer[nbytes-1] = 0;

	if(bytes_read == -1)
		check_error(false,"");
	
	if(write(*fd,buffer,bytes_read) == -1)
		check_error(false,"");
	
}
else if(mode[0] == '-' && mode[1] == 'a'){

	flags |= O_WRONLY;
	flags |= O_APPEND;
	flags |= O_CREAT;
	*fd = open(fpath,flags,defaultMode);

	char buffer[MAX_SIZE];
	size_t nbytes = sizeof(buffer);
	ssize_t bytes_read;

	bytes_read = read(0,buffer,nbytes);

	buffer[nbytes-1] = 0;

	if(bytes_read == -1)
		check_error(false,"");
	
	if(write(*fd,buffer,bytes_read) == -1)
		check_error(false,"");


}
else
	return false;



return true;

}

int main(int argc,char **argv){

check_error(argc == 3,"");

int fd;

check_error(os_file_open(argv[2],argv[1],&fd),"");

exit(EXIT_SUCCESS);
}
	








