1. **Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.**

`./mlfq.py -j 2 -n 2 -m 15 -M 0 -c`

2. **How would you run the scheduler to reproduce each of the examples in the chapter?**
Figure 8.2: `./mlfq.py --jlist 0,200,0 --quantum 10 --numQueues 3 -c` 
Figure 8.3: `./mlfq.py --jlist 0,180,0:100,20,0 --quantum 10 --numQueues 3 -c`
Figure 8.4: `./mlfq.py --jlist 0,170,0:50,30,1 --iotime 4 -S -c`
#TODO ...


3. **How would you configure the scheduler parameters to behave just like a round-robin scheduler?**
Using only one queue ensures that processes are timesliced just like RR.
`./mlfq.py --numQueues 1 -c`

4. **Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval.**
`./mlfq.py --jlist 0,50,9:0,20,0 --quantum 10 --iotime 1 -S -c`

5. **Given a system with a quantum length of 10 ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single longrunning (and potentially-starving) job gets at least 5% of the CPU?**
Every 200ms.


6. **One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.**
