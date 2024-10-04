#define _XOPEN_SOURCE 700

#include <stdio.h>

#include <stdlib.h>

#include <errno.h>

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	perror(msg);\
	exit(EXIT_SUCCESS);\
	}\
	}while(0)

#define MAX_STRING 256

// ./a.out fajl_sa_recima fajl_koji_se_menja
int main(int argc,char **argv){

if(argc !=3)
	return 1;

FILE *reci;

reci = fopen(argv[1],"r");
if(reci == NULL)
	check_error(0,"fopen");

int broj;
char string[MAX_STRING];

while(fscanf(reci,"%d %s",&broj,string) == 2)
	{
		FILE *menja;
		check_error(menja = fopen(argv[2],"r+b"),"...");

		fseek(menja,broj,SEEK_SET);
		fputs(string,menja);
		fclose(menja);
	}

fclose(reci);


exit(EXIT_SUCCESS);
}

