#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isJPG(char *path) {
	FILE *file = fopen(path, "rb");
}

int validateFiles(int argc, char **argv[]) {
	if (argc != 2) {
		printf("usage: jpgVal <filepath> OR jpgVal <dirpath>\n");
		return 1;
	}
	printf("%s", argv[1]);
}

int main(int argc, char **argv[]) {
	return validateFiles(argc, argv);
}

