# Virtual Memory

- Process: running program
	- Registers
	- Memory State (code, heap, stack) [virtual address space]

- Goals: large memory, private (protected) memory, efficient memory.
- Efficiency: Limited Direct Execution (loads, stores, instant fetch)


## Mechanisms
- hardware support;
- os support;

When do memory access occur?
- instruction fetch;
- explicit loads (mem -> CPU), stores (CPU -> mem);

Address translation: on every memory reference, translate virtual memory address into physical memory address

### Mechanism 1: Dynamic relocation or base/bounds
Process P1 has an address space AS1.
Process P2 has an address space AS2.

RAM -> 0[       [...AS1...]  [...AS2...]  ]8000Kb

CPU has a Memory Management Unit (MMU), which has 2 registers (each CPU has their own MMU and registers).
Register 1 is called **base**: the address in physical memory
Register 2 is called **bounds**: where the AS of the currently running process starts

**every address in user program is a VIRTUAL ADDRESS**
Virtual Address (VA) to Physical Address (PA): VA + base (offset) = PA, if it's within the bounds

Base register: translation
Bounds register: protection (check if it's within the address space)

On every memory access, the MMU checks if the memory is within the AS for that process. If it's not, the hardware raises an exception, traps into the trap table and the process gets killed.

Base/bounds: **fast and simple** but it's hard to allocate contigously, hard to expand and hard to share memory between processes.

#### Roles of the OS:
- when context switching, the OS needs to store the current process' base/bounds and restore the next process' base/bounds. Instructions to do this will need to run on privileged mode.
- defragment the physical memory. Ideally, a process' AS should be one contiguous chunk of memory and all the free memory must also be one contiguous chunk of memory.

RAM: from [       [...AS1...]      [...AS2...]    ]  to [[...AS2...][...AS1...]                 ]

- stop processes before reallocating their AS.
- copy the process' AS to new location, carefully
- change the base to new value
- make the process' runnable again

- on a malloc() call, the OS needs to change the bounds register (after zeroing the memory, for security reasons)

#### Generalizing base/bounds:
- segmentation: multiple base/bounds per process, one per logic region of AS.

virtual memory
[[code][heap ->]        [<- stack]]

physical memory
[[code]      [<- stack]  [heap ->]]

- no waste
- os roles: still has to defrag memory, still has to save base/bound pairs, manage malloc() calls.
