#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	if (argc == 1) {
		printf("usage: wzip file1 [file2 ...]\n");
		exit(1);
	}


	for (int i = 1; i < argc; i++) {
		FILE *fp = fopen(argv[i], "r");
		
		if(fp == NULL) {
			printf("wzip: cannot open file.\n");
			exit(1);
		}

		char curr = fgetc(fp);
		while(1) {
			int count = 1;
			char prev = curr;

			while(1) {
				curr = fgetc(fp);
				if(curr != prev) break;
				count++;
			}

			if (curr == EOF) break;
			fwrite(&count, sizeof(int), 1, stdout);
			printf("%c", prev);
		}
		fclose(fp);
	}

	return 0;
}
