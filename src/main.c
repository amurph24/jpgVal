#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>

int isJPG(char *path) {
	FILE *file = fopen(path, "rb");
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
		// isJPG(argv[1]);
		return 0;
	}

	printf("'%s' is a dir, checking contents...\n", argv[1]);
		// for (...)
		// {
		// *recursion*
		// }
	// END recursion
	return 0;
}

int main(int argc, char **argv) {
	return validateFiles(argc, argv);
}

