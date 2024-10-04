#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <ftw.h>

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	perror(msg);\
	fprintf(stderr,"File:%s\nFunction: %s\nLine:%d\n",__FILE__,__func__,__LINE__);\
	exit(EXIT_FAILURE);\
	}\
}while(0)

#define DAY_IN_SEC (24*60*60)

int filterByTime(const char* fpath,const struct stat* sb,int typeflag,struct FTW* ftwbuf){

time_t now = time(NULL);
time_t diffInSec = now - sb->st_mtime;

printf("%d\n",((int)diffInSec)/DAY_IN_SEC);

return 0;
}

int main(int argc,char ** argv){

check_error(argc == 2,"argc");

struct stat fInfo;

check_error(stat(argv[1],&fInfo)!= -1,"Stat");
//check_error(S_ISDIR(fInfo.st_mode),"dir");

check_error(nftw(argv[1],filterByTime,50,0) != -1,"nftw");


exit(EXIT_SUCCESS);

}







