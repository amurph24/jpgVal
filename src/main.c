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

#define SELF "."
#define PARENT ".."

void print_indent(int tabs) {
	printf("%*s", 4*tabs, "");
}

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
			printf("%s exceeds max file size: %d bytes\n", path, MAX_BYTES);
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
	return isJPG;
}

int validateFiles(char *path, int depth) {
	// validate path
	if (access(path, F_OK)) {
		printf("'%s' cannot be accessed\n", path);
		return 1;
	}
	
	DIR *dir = opendir(path);

	// do something for files	
	if (!dir) {
		if (isFilePathJPG(path)) {
			printf("%s - VALID\n", path);
		} else {
			printf("%s - INVALID\n", path);
		}
		
		return 0;
	}
	
	// path is dir, setup recursive call
	
	char *childPath = (char*)malloc(30 * sizeof(char));
	char *selfDir = SELF, *parentDir = PARENT;

	struct dirent *dirChild;
	char slash = '/';
	
	printf("\n'%s' is a dir, checking contents...\n", path);
	while ((dirChild = readdir(dir)) != NULL) {
		
		// don't recursively call self or parent dir
		if (!strcmp(dirChild->d_name, selfDir) | !strcmp(dirChild->d_name, parentDir)) continue;

		// get new path for recursive call	
		strcpy(childPath, path);
		strncat(childPath, &slash, 1);
		strcat(childPath, dirChild->d_name);

		//recursion
		validateFiles(childPath, depth + 1);
	}

	closedir(dir);
	return 0;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("usage: jpgVal <filepath> OR jpgVal <dirpath>\n");
		return 1;
	}

	return validateFiles(argv[1], 0);
}

