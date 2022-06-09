
### [Code](https://pages.cs.wisc.edu/~remzi/Classes/537/Spring2018/Book/cpu-api.pdf)
1. **Write a program that calls fork(). Before calling fork(), have the  
main process access a variable (e.g., x) and set its value to some-  
thing (e.g., 100). What value is the variable in the child process?  
What happens to the variable when both the child and parent change  
the value of x?
- Each of the processes has its own variable, so if the child modifies it, it doesn't  affect the parent, or vice-versa.
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
        int rc = fork();
        int x = 100;

        if (rc < 0) {
                printf("fork failed\n");
                exit(1);
        }

        if (rc == 0) {
                x = 120;
                printf("Child process. x is %d\n", x);
        } else {
                wait(NULL);
                printf("Parent process. x is %d\n", x);
        }

        return 0;
}

// this program prints:
// Child process. x is 120
// Parent process. x is 100
```

2. **Write a program that opens a file (with the open() system call)  
and then calls fork() to create a new process. Can both the child  
and parent access the file descriptor returned by open()? What  
happens when they are writing to the file concurrently, i.e., at the  
same time?
- Both processes can access the file, the order depends on the OS scheduler.
```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
        FILE *fp = fopen("shared_file", "w");
        int rc = fork();

        if (rc < 0) {
                printf("fork failed\n");
                exit(1);
        }
        if (fp == NULL) {
                printf("file open failed\n");
                exit(1);
        }

        if (rc == 0) {
                fprintf(fp, "this is the child\n");
        } else {
                fprintf(fp, "this is the parent\n");
        }

        return 0;
}

// the contents of the file "shared_file" is either:
// this is the child
// this is the parent
// or
// this is the parent
// this is the child
// the order depends on how the processes are scheduled by the os
```

3. **Write another program using fork(). The child process should  
print “hello”; the parent process should print “goodbye”. You should  
try to ensure that the child process always prints first; can you do  
this without calling wait() in the parent?

?? #todo

4. **Write a program that calls fork() and then calls some form of exec() to run the program /bin/ls. See if you can try all of the variants of exec(), including (on Linux) execl(), execle(), execlp(), execv(), execvp(), and execvpe(). Why do you think there are so many variants of the same basic call?
https://en.wikipedia.org/wiki/Exec_(system_call)#C_language_prototypes
- `execv()` , `execvp()`, `execvpe()` functions provide an array of pointers to null-terminated strings that represent the agument list available to the new program.
- `execle()` and `execvpe()` functions allow the caller to specify the environment of the executed program via the agument `evnp`
```c
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
                char *cmdargs[] = {strdup("touch"), strdup("new_file"), NULL};
                execvp(cmdargs[0], cmdargs);
        }

        return 0;
}
```

5. **Now write a program that uses `wait()` to wait for the child process to finish in the parent. What does `wait()` return? What happens if you use `wait()` in the child?
- `wait()` returns the PID of the terminated child process on success. On error it returns `-1`. `wait()` always returns `-1` on the child process.
```c
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
```

6. 