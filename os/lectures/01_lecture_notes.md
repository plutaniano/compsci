# Operating Systems
## Why study operating systems?
- **Security**: protecting information;
- **Programs**: running programs concurrently and efficiently;
- **Reliability**: ensuring stable operation on adverse conditions;
- **File/programs management**: managing files and programs;
- **Understanding how computers work**

---

## Overview of the course

CPU <-> RAM <-> Storage <-> IO
Fetch -> Decode -> Execute Cycle

Understanding C and why the code below prints 10.
```C
void inc(int x)
{
	x = x + 1;
}

int y = 10;
inc(y);
printf("%d", y) // prints 10, not 11
```

Understanding the code, the heap, and the stack.

```c
// cpu.c
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: cpu <string>\n");
		exit(1);
	}
	
	char *str = argv[1];
	while (1) {
		printf("%s\n", str);
		Spin(1);
	}
	return 0;
}
```

Compiling and running
```bash
$ gcc gpu.c -o cpu -Wall -Werror

# Running 3 instances of the program in parallel
./cpu 1 &; ./cpu 2 &; ./cpu 3 &;
1
2
3
1
2
3
1
2
3
^C
```

```c
// threads.c
void *worker(void *arg)
{
	int i;
	for (i = 0; i < loops; i++) {
		counter++;
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "usage: threads <loops>\n");
		exit(1);
	}
	loops = atoi(argv[1]);
	pthread_t p1, p2;
	printf("Initial value: %d\n", counter);
	Pthread_create(&p1, NULL, worker, NULL);
	Pthread_create(&p2, NULL, worker, NULL);
	Pthread_join(p1, NULL);
	Pthread_join(p2, NULL);
	printf("Final value: %d\n");
	return 0;
}
```

Running this program may not produce the result expected
```bash
$ ./threads 1000
Initial value: 0
Final value: 2000

$ ./threads 100000
Initial value: 0
Final value: 136323 # should've been 200000
```

---

## Virtualization
One physical "thing" => Many virtual "thing"s
- Virtualizing CPU
- Virtualizing RAM

Each running program thinks that it has its own private CPU and its own memory space.

Key aspects:
- Efficiency
- Security (restricted)

### CPU Virtualization
1 CPU => Many virtual CPUs

#### Time sharing
A | B | A | B | A
time ---> 

#### Process
"A running program"

Components of a process:
- Memory: private access, "address space". Holds the code, stack and the heap.
- Registers: Program Counter (PC), Stack Pointer (SP), General Purpose Regs.
- IO State: open files.

### Mechanisms
Core mechanism: **Limited Direct Execution**

"**Direct Execution**": Running programs directly on the CPU. The program has access to everything, but it's very fast because it doesnt have to share CPU or memory with other programs.

"**Limited**": Security. Limits what a program can do via the OS.

If you ran a program "A", what if it wanted to do something restricted? 
What if the user wants to stop program "A" and run program "B"?
What if it does something that's very slow (disk I/O)?

When you run programs on direct access, that program takes over the entire hardware and you lose control of how it executes. It simply does what it it's programmed to do, no matter what.
Sometimes it's desirable to limit what a program can do.

#### Problem #1: restricted operations
2 modes: one bit per mode
- OS (kernel mode): the OS can do anything.
- User program (user mode): can only do a limited number of things

**How to get into these modes? how to transition from one mode to another?**
At boot time, start in *kernel mode*. 
When the user wants to run a program, executes a special instruction that: 1) transitions into *user mode* and 2) jumps to some location in user program.

**How to do something restricted in user mode (disk I/O)?**
Execute a special instruction that goes into *kernel mode*, that verifies if what the program wants to do is allowed, if it passes, executes the instruction and jumps back to user program.

**The 2 special instructions**:
- Trap: jump into the kernel at a restricted, known to be safe, location, saving the register state.
- Return: restores the register state as it was when trap was called and returns to the running program.

At boot time, the OS sets up a Trap Table, a place in memory where it stores the code that it is executed when a certain trap is called.

#### Problem #2: how to stop A to run B?
- Cooperative approach: hope that A doesn't refuse to give back control to the OS.
- Non-cooperative approach: use a timer interrupt.

**Timer interrupt**
At boot time, the OS installs the trap handlers and starts the interrupt timer.
Then A is executed.
Sometime after A is executed, the timer expires, a interrupt is raise and the OS takes back control.