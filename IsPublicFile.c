#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>
#include <pwd.h>
#include <grp.h>

#define check_error(cond,userMsg)\
	do{\
		if(!(cond)){\
			perror(userMsg);\
			exit(EXIT_FAILURE);\
			}\
	}while(0)

bool osIsPublicFile(const char *fpath);

int main(int argc,char ** argv){

if(argc != 2)
	exit(EXIT_FAILURE);

bool os = osIsPublicFile(argv[1]);

if(os == true)
	printf("true");
else
	{printf("false");}

exit(EXIT_SUCCESS);
}

bool osIsPublicFile(const char *fpath){

	struct stat fInfo;
	check_error(stat(fpath,&fInfo)!=-1,"stat failed");

	char pravaPristupa[11];
	strcpy(pravaPristupa,"-rwxrwxrwx");

	switch(fInfo.st_mode & S_IFMT){

	case S_IFREG:
		pravaPristupa[0] = '-';
		break;
	case S_IFDIR:
		pravaPristupa[0] = 'd';
		break;	
	case S_IFCHR:
		pravaPristupa[0] = 'c';
		break;	
	case S_IFBLK:
		pravaPristupa[0] = 'b';
		break;	
	case S_IFLNK:
		pravaPristupa[0] = 'l';
		break;	
	case S_IFIFO:
		pravaPristupa[0] = 'p';
		break;	
	case S_IFSOCK:
		pravaPristupa[0] = 's';
		break;	
}

	if(!(fInfo.st_mode & S_IRUSR))
		pravaPristupa[1] = '-';
	if(!(fInfo.st_mode & S_IWUSR))
		pravaPristupa[2] = '-';
	if(!(fInfo.st_mode & S_IXUSR))
		pravaPristupa[3] = '-';
	if(!(fInfo.st_mode & S_IRGRP))
		pravaPristupa[4] = '-';
	if(!(fInfo.st_mode & S_IWGRP))
		pravaPristupa[5] = '-';
	if(!(fInfo.st_mode & S_IXGRP))
		pravaPristupa[6] = '-';
	if(!(fInfo.st_mode & S_IROTH))
		pravaPristupa[7] = '-';
	if(!(fInfo.st_mode & S_IWOTH))
		pravaPristupa[8] = '-';
	if(!(fInfo.st_mode & S_IXOTH))
		pravaPristupa[9] = '-';

	if(pravaPristupa[7] == 'r' && pravaPristupa[8] == 'w')
		return true;
	else
		return false;

}








