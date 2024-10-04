//program who is encrypting password from shadow file using encrypting process with username from TLPI
#define _BSD_SOURCE

#define _XOPEN_SOURCE 500

#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdbool.h>
#include <errno.h>
#include <ftw.h>
#include <string.h>
#include <fcntl.h>

#include <crypt.h>

#define check_error(cond,msg)\
do{\
	if(!(cond)){\
	perror(msg);\
	fprintf(stderr,"File:%s\nFunction:%s\nLine:%d\n",__FILE__,__func__,__LINE__);\
	exit(EXIT_FAILURE);\
	}\
}while(0)


char* pronadjiImeVlasnika(uid_t uid){

	struct passwd* userInfo = getpwuid(uid);

	if(userInfo == NULL)	
		return NULL;

	
	char* userName = malloc(strlen(userInfo->pw_name) + 1);
	if(userName == NULL)
		return NULL;

	strcpy(userName,userInfo->pw_name);

	return userName;
}

int main(int argc, char *argv[])
{
	check_error(argc == 2,"Nije unesena putanja do fajla.\n");

	char *username,password[100],*encrypted,*p;
	struct passwd *pwd;
	struct spwd *spwd;
	size_t len;
	long lnmax;
	

	lnmax = sysconf(_SC_LOGIN_NAME_MAX);
	if(lnmax == -1)
	   lnmax = 256;

	username = malloc(lnmax);
	if(username == NULL)
		exit(EXIT_FAILURE);
	//

	//
	
	struct stat fInfo;

	check_error(stat(argv[1],&fInfo)!=-1,"stat failed");
	
	printf("Vlasnik fajla u kome se trazi sifra je:");
	fflush(stdout);

	//fInfo->gid - i onda nadjem ime
	
	char* userName = pronadjiImeVlasnika(fInfo.st_uid);

	printf("%s\n",userName);
	
	strcpy(username,userName);

	len = strlen(username);
	if(username[len - 1] == '\n')
		username[len-1] = '\0';

	pwd = getpwnam(username);
	
	if(pwd == NULL)
		{printf("coudn't get password record\n");exit(EXIT_FAILURE);}
	spwd = getspnam(username);
	if(spwd == NULL && errno == EACCES)
		{printf("no permission to read shadow password file\n");exit(EXIT_FAILURE);}
	if(spwd != NULL)
		pwd->pw_passwd = spwd->sp_pwdp;
	//
	FILE *fp;

	fp = fopen(argv[1],"r");
	
	check_error(fp != NULL,"file\n");	

	char buf[100];
	bool pronadjeno = false;

	while(fscanf(fp,"%s",buf) == 1)
	{
		//printf("%s\n",buf);
		
		if(strcmp(buf,"Password:")==0)		
			{
			fscanf(fp,"%s",password);
			pronadjeno = true;
			}
	}
	fclose(fp);
	if(pronadjeno == true)
	printf("Pronadjena je sifra:%s\ni ona je",password);
	
	else{
	printf("Nije pronadjena sifra.\n");
	exit(EXIT_FAILURE);	
	}
	//strcpy(password,"student");
	
	encrypted = crypt(password,pwd->pw_passwd);
	
	//printf("\n\n%s\n\n",encrypted);

	for(p = password;*p != '\0'; )
		*p++ = '\0';

	if(encrypted == NULL)
		{printf("crypt");exit(EXIT_FAILURE);}

	//printf("\n%s\n%s\n",encrypted,pwd->pw_passwd);

	
	if(!(strcmp(encrypted,pwd->pw_passwd) == 0)){

	printf(", neodgovarajuca sifra.\n");
	exit(EXIT_FAILURE);

	}
	
	printf(", uspesna:UID=%ld\n",(long)pwd->pw_uid);

	exit(EXIT_SUCCESS);	
}
