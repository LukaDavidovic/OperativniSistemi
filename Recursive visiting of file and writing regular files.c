/* Program obilazi direktorijum i racuna njegove velicinu
 *
 * Primer poziva:
 * ./sizeOfDir dirPath
 */
#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <dirent.h>

#include <string.h>

#define check_error(cond,userMsg)\
	do {\
		if (!(cond)) {\
			perror(userMsg);\
			exit(EXIT_FAILURE); \
		}\
	} while(0)

char *ext = NULL;
int brojac=0;

void sizeOfDir(char* putanja) {
		
	struct stat fInfo;
	check_error(lstat(putanja, &fInfo) != -1, "...");
	
	
	
	
	if (!S_ISDIR(fInfo.st_mode)) {

		if(S_ISREG(fInfo.st_mode)){
		
		char *fExt = strrchr(putanja,'.');
	
		if(fExt != NULL && !strcmp(fExt,ext))

			brojac++;	

		}	
		return;
		}
		
		
	
	
	
	DIR* dir = opendir(putanja);
	check_error(dir != NULL, "...");
	
	
	struct dirent* dirEntry = NULL;
	errno = 0;
	while ((dirEntry = readdir(dir)) != NULL) {
		
		char* path = malloc(strlen(putanja) + strlen(dirEntry->d_name) + 2);
		check_error(path != NULL, "...");
		
	
		strcpy(path, putanja);
		strcat(path, "/");
		strcat(path, dirEntry->d_name);
		
		
		if (!strcmp(dirEntry->d_name, ".") || !strcmp(dirEntry->d_name, "..")) {
			
			check_error(stat(path, &fInfo) != -1, "...");
			
			
			free(path);
			errno = 0;
			
			continue;
		}
		
		sizeOfDir(path);
		free(path);
		
		errno = 0;
	}
	
	check_error(errno != EBADF, "readdir");
	
	check_error(closedir(dir) != -1, "...");	
}

int main(int argc, char** argv) {
	
	check_error(argc == 3, "...");
	
	ext = argv[2];

	struct stat fInfo;
	check_error(stat(argv[1], &fInfo) != -1, "...");
	
	check_error(S_ISDIR(fInfo.st_mode), "nije dir");
	
	sizeOfDir(argv[1]);
	
	printf("%d\n", brojac);
	
	exit(EXIT_SUCCESS);
}
