### [Simulation](https://pages.cs.wisc.edu/~remzi/Classes/537/Spring2018/Book/cpu-intro.pdf)
1. **Run process-run.py with the following flags: -l 5:100,5:100. What should the CPU utilization be (e.g., the percent of time the CPU is in use?) Why do you know this? Use the -c and -p flags to see if you were right.**
- 100%
- Because there's no I/O, only processing, so the CPU never has to wait for something.

2. **Now run with these flags: ./process-run.py -l 4:100,1:0. These flags specify one process with 4 instructions (all to use the CPU), and one that simply issues an I/O and waits for it to be done. How long does it take to complete both processes? Use -c and -p to find out if you were right.**
- 11 cycles. First, the first process uses 4 cycles of the CPU, then the second process issues an I/O request (1 cycle), waits for 5 cycles, then process the I/O response (1 cycle).

3. **Switch the order of the processes: -l 1:0,4:100. What happens now? Does switching the order matter? Why? (As always, use -c and -p to see if you were right)**
- Now the first processes issues an IO request first, and while it's waiting, instead of doing nothing like in the last example, the CPU jumps to the second process and executes it. When it's done with the second processes, it returns to to the first one to see that the IO is done, because it was done while the CPU was running the second process. Order matters because if you issue an IO request before using the CPU, the computer can to both simultaneously.

4. **We’ll now explore some of the other flags. One important flag is -S, which determines how the system reacts when a process issues an I/O. With the flag set to SWITCH ON END, the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished. What happens when you run the following two processes (-l 1:0,4:100  -c -S SWITCH ON END), one doing I/O and the other doing CPU  work?**
- It blocks the computer from using the waiting time during IO to execute other processes. It can't efficiently use the time it has.

5. **Now, run the same processes, but with the switching behavior set to switch to another process whenever one is WAITING for I/O (-l 1:0,4:100 -c -S SWITCH ON IO). What happens now? Use -c and -p to confirm that you are right.**
- The CPU sees that it's going to have to wait for IO to be done for process 0, so it switches to process 1 to execute it while it waits for IO to be done.

6. **One other important behavior is what to do when an I/O completes. With -I IO RUN LATER, when an I/O completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running. What happens when you run this combination of processes? (Run ./process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH ON IO -I IO RUN LATER -c -p) Are system resources being effectively utilized? **
- The CPU issues the first IO request from process 0 and efficiently switches to process 1, but instead of issuing the second IO request from process 0 when the first IO is done, it executes all other processes. This causes the IO requests to pile up at the end, instead of being interlaced between the CPU processing.

7. **Now run the same processes, but with -I IO RUN IMMEDIATE set, which immediately runs the process that issued the I/O. How does this behavior differ? Why might running a process that just completed an I/O again be a good idea?**
- This behaviour prioritizes always having an IO request being processed in the background. This is a good ideia because it decreases the chance that the CPU will have to wait for IO to be complete at the end of all the processes.

8. **Now run with some randomly generated processes: -s 1 -l 3:50,3:50 or -s 2 -l 3:50,3:50 or -s 3 -l 3:50,3:50. See if you can predict how the trace will turn out. What happens when you use the flag -I IO RUN IMMEDIATE vs. -I IO RUN LATER? What happens when you use -S SWITCH ON IO vs. -S SWITCH ON END?**
- Using SWITCH_ON_END the programs take much longer to complete because the CPU wastes a lot of time waiting for IO to be done compared to when using SWITCH_ON_IO.
- Using IO_RUN_IMMEDIATE vs IO_RUN_LATER doesnt make a difference in the cases provided, because all processes are IO bound.
