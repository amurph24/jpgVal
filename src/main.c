#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_BYTES 20000000
#define FF 255
#define D8 216
#define D9 217


int isFileJPG(FILE *file, char *path) {
	int counter = 0;
	unsigned char fileBytes[2]; 
	fileBytes[0] = getc(file);
	fileBytes[1] = getc(file);

	// to check for file end
	int temp = getc(file);

	// validate first two bytes of file
	if (fileBytes[0] != FF || fileBytes[1] != D8) {
		return 0;
	}
	
	// move "buffer" over bytes
	do {
		if (counter >= MAX_BYTES) {
			printf("%20s exceeds max file size: %d bytes\n", path, MAX_BYTES);
			return 0;
		}
		// move "buffer" forward
		fileBytes[0] = fileBytes[1];
		fileBytes[1] = temp;
		
		// get next byte
		temp = getc(file);
	} while (temp != EOF); 

	// validate last two bytes of file
	if (fileBytes[0] != FF || fileBytes[1] != D9) {
		return 0;
	}
	
	return 1;
}


int isFilePathJPG(char *path) {
	// pass file to checker
	FILE *file = fopen(path, "rb");
	int isJPG = isFileJPG(file, path);
	fclose(file);

	// print invalid files to console
	if (!isJPG) {
		printf("%30s - INVALID\n", path);
	}

	return isJPG;
}

int validateFiles(char *path) {
	// START recursion
	// validate path
	if (access(path, F_OK)) {
		printf("'%s' cannot be accessed\n", path);
		return 1;
	}
	
	// determine file or dir
	DIR *dir = opendir(path);
	
	if (!dir) {
		if (isFilePathJPG(path)) {
			printf("%30s is a valid jpg image\n", path);
		}
		
		return 0;
	}
	
	// path is dir, start checking contents
	
	char *childPath = (char*)malloc(30 * sizeof(char));
	struct dirent *dirChild;
	char slash = '/';
	
	printf("'%s' is a dir, checking contents...\n", path);
	while ((dirChild = readdir(dir)) != NULL) {
		printf("%s\n", dirChild->d_name);
		
		// get path of child	
		strcpy(childPath, path);
		strcat(childPath, &slash);
		strcat(childPath, dirChild->d_name);
		printf("%s\n", childPath);
	}

	closedir(dir);
	// END recursion
	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("usage: jpgVal <filepath> OR jpgVal <dirpath>\n");
		return 1;
	}

	return validateFiles(argv[1]);
}

