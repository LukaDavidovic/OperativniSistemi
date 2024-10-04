#define _XOPEN_SOURCE 700

#include <ftw.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	perror(msg);\
	exit(EXIT_FAILURE);\
	}\
	}while(0)

char *ext = NULL;

int prikaz(const char* fpath,const struct stat *sb,int typeflag,struct FTW *ftwbuf){

if(ftwbuf->level >= 2 && ftwbuf->level <= 5){

if(typeflag == FTW_F){

	char *fext = strrchr(fpath + ftwbuf->base,'.');
	
	if(fext != NULL && !strcmp(fext,ext))
	{	
		char *relativna = strrchr(fpath,'/');
		char relativna1[100];
		strcpy(relativna1,relativna+1);		

		printf("%-80s\n",relativna1);
	}

}

}
return 0;

}

int main(int argc,char **argv){

check_error(argc == 3,"...");

ext = argv[2];

struct stat fInfo;
check_error(stat(argv[1],&fInfo) != -1,"stat");
check_error(S_ISDIR(fInfo.st_mode),"not a dir");

check_error(nftw(argv[1],prikaz,50,0) != -1,"nftw");

exit(EXIT_SUCCESS);
}
