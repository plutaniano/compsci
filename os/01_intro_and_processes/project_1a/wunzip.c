#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("usage: wunzip file1 [file2 ...]\n");
		exit(1);
	}

	int count;
	char letter;

	for (int i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		
		if(fp == NULL) {
			printf("wunzip: cannot open file.\n");
			exit(1);
		}

		while(!feof(fp)) {
			fread(&count, sizeof(int), 1, fp);
			fread(&letter, sizeof(char), 1, fp);

			for(int i = 0; i < count; i++) {
				printf("%c", letter);
			}
		}

		fclose(fp);
	}

	return 0;
}
