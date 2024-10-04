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

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	perror(msg);\
	fprintf(stderr,"File: %s\nFunction: %s\nLine: %d\n",__FILE__,__func__,__LINE__);\
	exit(EXIT_FAILURE);\
	}\
	}while(0)

void pravapristupa(const char *fpath){

struct stat finfo;

check_error(stat(fpath,&finfo)!=-1,"stat");

char pravaPristupa[11];

strcpy(pravaPristupa,"-rwxrwxrwx");

switch(finfo.st_mode & S_IFMT){

case S_IFIFO:
	pravaPristupa[0] = 'p';
	break;
case S_IFCHR:
	pravaPristupa[0] = 'c';
	break;
case S_IFDIR:
	pravaPristupa[0] = 'd';
	break;
case S_IFBLK:
	pravaPristupa[0] = 'b';
	break;
case S_IFREG:
	pravaPristupa[0] = '-';
	break;
case S_IFSOCK:
	pravaPristupa[0] = 's';
	break;
case S_IFLNK:
	pravaPristupa[0] = 'l';
	break;
}

if(!(finfo.st_mode & S_IRUSR))
	pravaPristupa[1] = '-';
if(!(finfo.st_mode & S_IWUSR))
	pravaPristupa[2] = '-';
if(!(finfo.st_mode & S_IXUSR))
	pravaPristupa[3] = '-';
if(!(finfo.st_mode & S_IRGRP))
	pravaPristupa[4] = '-';
if(!(finfo.st_mode & S_IWGRP))
	pravaPristupa[5] = '-';
if(!(finfo.st_mode & S_IXGRP))
	pravaPristupa[6] = '-';
if(!(finfo.st_mode & S_IROTH))
	pravaPristupa[7] = '-';
if(!(finfo.st_mode & S_IWOTH))
	pravaPristupa[8] = '-';
if(!(finfo.st_mode & S_IXOTH))
	pravaPristupa[9] = '-';


printf("%s\n",pravaPristupa);

}


int main(int argc,char **argv){

if(argc == 2,"...");

pravapristupa(argv[1]);

exit(EXIT_SUCCESS);

}


