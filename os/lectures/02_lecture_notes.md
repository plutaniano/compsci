```c
// pseudocode
while(1) {
    instruction = fetch(ProgramCounter);
    decoded = decode(instruction):
    ProgramCounter++;
    execute(decoded) // might change ProgramCounter
    processInterrupts()
}
```

before executing, check permission

```c
void execute(void instruction) {
    bool permitted = checkPermission();
    if (permitted) {
        Execute(instruction)
    } else {
        raise Exception // this gets handled by the OS
    }
}
```

```c
// this is run by the OS, in kernel mode
void processInterrupts() {
    if(interrupts_pending) {
        go_to(trap_table[interrupt])
    }
}
```

## CPU virtualiation mechanisms:
### OS: implement limited direct execution

@boot time (kernel mode):
- OS runs first
- set up trap/exception/interrupt handlers
- start interrupt timer
- ready to running user programs

@user program runs (user mode):
- program wants a OS service, calls a trap (syscalls: `exec()`, `wait()`, `exit()`, `fork()`; network, I/O)
- transition into kernel mode from user mode
- save register state, to restore when trap is done
- OS runs the trap handler
- restore registers
- OS returns from trap

#### Timer interrupt
A way to regain control of the CPU (by the OS).
- the timer periodically raises a trap
- OS handles the trap
- switches to a new process

### Process List

The OS needs to track all the different running processes in the system. 

per-process info:
- state: RUNNING, READY, BLOCKED (by IO)...
...

#### Problem #3: slow operations (I/O)

What to do when the system is waiting for slow operations?

## Scheduling processes

Run A to completion then B? Or run A for a bit, then B for a bit, then A again?

#### Assumptions:
- all jobs arrive at the same time
- each jobs only uses CPU
- each jobs runs for some amount of time T
- T is the same for all processes
- there's a metric that we care about: turnaround time (end time - time arrived)

Example: jobs A,B,C all arrive at Ti=0 and each runs for 5 time units

**FIFO Scheduler**: A is run to completion, then B is run to completion, then C in run to completion.
```
AAAAABBBBBCCCCC
---> time

Avg time to completion = (5 + 10 + 15) / 3 = 11.67
```

*Relax that all jobs have the same runtime T*
Worst case scenario for FIFO:
Ta = 15; Tb=1; Tc=1
```
AAAAAAAAAAAAAAABC

Avg time to completion = (15 + 16 + 17) / 3 = 16
B and C wait a long time, even if they're short jobs
```

Goal: schedule **shortest job first** (SJF)

*Relax that all jobs arrive at the same time*
B arrives when A is already running
A is 10tu in a 100tu job, B is 10tu
Should the CPU switch to B then come back to A?

**shortest time to completion first** (STCF)

new metric: response time, how long a process waits before it first runs?

new policy: **Round robin**, run A for a bit, then B for a bit, then C for a bit, then A again...
Each "bit" is a multiple of the timer interrupt

round robin trade off: if the time slices are too small, too much time is wasted in context switches.

How to build a scheduler that balances all these trade-offs?