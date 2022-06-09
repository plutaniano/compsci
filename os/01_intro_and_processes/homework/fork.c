#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int rc = fork();

	if (rc < 0) {
		printf("fork failed\n");
		exit(1);
	}

	if (rc == 0) {
		fprintf(stdout, "child\n");
	} else {
		wait(NULL);
		fprintf(stdout, "parent\n");
	}

	return 0;
}

