#define _XOPEN_SOURCE 700

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include <stdio.h>
#include <stdlib.h>

#define check_error(cond,msg)\
	do{\
	if(!(cond)){\
	perror(msg);\
	exit(EXIT_FAILURE);\
	}\
	}while(0)

int main(int argc,char **argv){

check_error(argc == 3 ,"...");

struct stat fInfo;

check_error(stat(argv[1],&fInfo) != -1,"...");

if(argv[2][0] == 'u'){

if(argv[2][1] == '+'){

	if(argv[2][2] == 'r'){
	// user dodaje se citanje
	
	fInfo.st_mode |= S_IRUSR;

	}
	else if(argv[2][2] == 'w'){
	//user dodaje se pisanje
	fInfo.st_mode |= S_IWUSR;	
	
	}
	else if(argv[2][2] == 'x'){
	//user dodaje se izvrsavanje valjda
	fInfo.st_mode |= S_IXUSR;

	}//u suprotnom greska
	else
	check_error(0,"...");

}
else if(argv[2][1] == '-'){//isto to samo se oduzimanja

	if(argv[2][2] == 'r'){
	fInfo.st_mode ^= S_IRUSR;
	
	}
	else if(argv[2][2] == 'w'){
	fInfo.st_mode ^= S_IWUSR;

	}
	else if(argv[2][2] == 'x'){

	fInfo.st_mode ^= S_IXUSR;

	}
	else//greska ako nije neko slovo
	check_error(0,"...");

}
else
	check_error(0,"...");//greska ako nije ni + ni -

}
else if(argv[2][0] == 'g'){

if(argv[2][1] == '+'){

	if(argv[2][2] == 'r'){
	
	fInfo.st_mode |= S_IRGRP;
	
	}
	else if(argv[2][2] == 'w'){
	
	fInfo.st_mode |= S_IWGRP;

	}
	else if(argv[2][2] == 'x'){

	fInfo.st_mode |= S_IXGRP;

	}
	else
	check_error(0,"...");

}
else if(argv[2][1] == '-'){

	if(argv[2][2] == 'r'){

	fInfo.st_mode ^= S_IRGRP;	
	
	}
	else if(argv[2][2] == 'w'){

	fInfo.st_mode ^= S_IWGRP;

	}
	else if(argv[2][2] == 'x'){

	fInfo.st_mode ^= S_IXGRP;

	}
	else
	check_error(0,"...");

}
else
	check_error(0,"...");

}
else if(argv[2][0] == 'o'){

if(argv[2][1] == '+'){

	if(argv[2][2] == 'r'){
	
	fInfo.st_mode |= S_IROTH;
	
	}
	else if(argv[2][2] == 'w'){

	fInfo.st_mode |= S_IWOTH;	

	}
	else if(argv[2][2] == 'x'){

	fInfo.st_mode |= S_IXOTH;

	}
	else
	check_error(0,"...");

}
else if(argv[2][1] == '-'){

	if(argv[2][2] == 'r'){

	fInfo.st_mode ^= S_IROTH;
	
	}
	else if(argv[2][2] == 'w'){
	
	fInfo.st_mode ^= S_IWOTH;

	}
	else if(argv[2][2] == 'x'){

	fInfo.st_mode ^= S_IXOTH;

	}
	else
	check_error(0,"...");

}
else
	check_error(0,"...");


}
else{
check_error(0,"greska");
}


check_error(chmod(argv[1],fInfo.st_mode) != -1,"...");

exit(EXIT_SUCCESS);
}












