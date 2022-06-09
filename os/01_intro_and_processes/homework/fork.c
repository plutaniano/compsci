#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//   A's stdout    pipe write   pipe read    B's stdin
// A <--------------------> PIPE <--------------------> B

int main(int argc, char *argv[]) {
	char str[100];
	int pidA, pidB;
	int pipefds[2]; // [read end, write end]
	pipe(pipefds);

	if( !(pidA = fork()) ) {
		// this runs on child A
		dup2(pipefds[1], 1);
		printf("this is child A");
	}

	if( !(pidB = fork()) ) {
		// this runs on child B
		dup2(pipefds[0], 0);
		fgets(str, 16, stdin);
		printf("child B read (%s) from child A\n", str);
	}

	return 0;
}

