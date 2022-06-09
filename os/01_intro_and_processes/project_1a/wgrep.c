#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
	// no search term and no file
	if (argc == 1) {
		printf("wgrep: searchterm [file ...]\n");
		exit(1);
	}

	char *searchterm = argv[1];

	// search term but no file
	if (argc == 2) {
		char buf[BUFFER_SIZE];
		while(fgets(buf, BUFFER_SIZE, stdin) != NULL) {
			if(strstr(buf, argv[1]) != NULL) {
				printf("%s", buf);
			}
		}
		exit(0);
	}

	// search term and file(s)
	for(int i = 2; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		if (fp == NULL) {
			printf("wgrep: cannot open file");
			exit(1);
		}
		char *line = NULL;
		size_t length = 0;
		while (getline(&line, &length, fp) != -1) {
			if (strstr(line, searchterm) != NULL) {
				printf("%s", line);
			}
		}
		fclose(fp);
	}

	return 0;
}







