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
			printf("%20s exceeds max file size of: %d bytes\n", path, MAX_BYTES);
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
	
	printf("%20s is a valid jpg file\n", path);
	return 1;
}

int isPathJPG(char *path) {
	// pass file to checker
	FILE *file = fopen(path, "rb");
	int isJPG = isFileJPG(file, path);
	fclose(file);

	// throw errors
	if (!isJPG) {
		printf("%20s is not a valid jpg file\n", path);
	}

	return isJPG;
}

int validateFiles(int argc, char **argv) {
	//validate usage
	if (argc != 2) {
		printf("usage: jpgVal <filepath> OR jpgVal <dirpath>\n");
		return 1;
	}
	
	// START recursion
	//validate path
	if (access(argv[1], F_OK)) {
		printf("'%s' does not exist\n", argv[1]);
		return 1;
	}
	printf("'%s' does exist\n", argv[1]);
	
	//check file or dir
	DIR *dir = opendir(argv[1]);
	if (!dir) {
		printf("'%s' is not a dir\n", argv[1]);
		isPathJPG(argv[1]);
		return 0;
	}

	printf("'%s' is a dir, checking contents...\n", argv[1]);
		// for (...)
		// {
		// *recursion call*
		// }
	// END recursion
	return 0;
}

int main(int argc, char **argv) {
	return validateFiles(argc, argv);
}

