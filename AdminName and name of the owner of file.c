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
	exit(EXIT_FAILURE);\
	}\
	}while(0)

void ispisi_user_ime(uid_t uid){

	struct passwd* userInfo = getpwuid(uid);
	
	printf("%s ",userInfo->pw_name);

}

void ispisi_group_ime(gid_t gid){

	struct group* groupInfo = getgrgid(gid);

	printf("%s\n", groupInfo->gr_name);

}


int main(int argc,char **argv){

check_error(argc == 2,"...");

struct stat finfo;

check_error(stat(argv[1],&finfo) != -1,"stat");

ispisi_user_ime(finfo.st_uid);
ispisi_group_ime(finfo.st_gid);

exit(EXIT_SUCCESS);
}


















