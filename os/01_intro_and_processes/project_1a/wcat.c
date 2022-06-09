#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[]) {
	char buffer[BUFFER_SIZE];

	for(int i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("my-cat: cannot open file\n");
			exit(1);
		}

		while (fgets(buffer, BUFFER_SIZE, fp) != NULL) {
			printf("%s", buffer);
		}
		fclose(fp);
	}

	return 0;
}
