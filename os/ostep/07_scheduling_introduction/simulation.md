# Simulation

1. **Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers**

**FIFO**: response time = (0 + 200 + 400) / 3 = 200 | turnaround time = (200 + 400 + 600) / 3 = 400

**SJF**: response time = (0 + 200 + 400) / 3 = 200 | turnaround time = (200 + 400 + 600) / 3 = 400

2. **Now do the same but with jobs of different lengths: 100, 200, and 300.**

**FIFO**: response time = (0 + 100 + 300) / 3 = 133.33 | turnaround time = (100 + 300 + 600) / 3 = 333.33

**SJF**: response time = (0 + 100 + 300) / 3 = 133.33 | turnaround time = (100 + 300 + 600) / 3 = 333.33

3. **Now do the same, but also with the RR scheduler and a time-slice of 1.**

**RR**: response time = (0 + 1 + 2) / 3 = 1 | turnaround time = (298 + 499 + 600) / 3 = 465.67

4. **For what types of workloads does SJF deliver the same turnaround times as FIFO?**

SJF and FIFO deliver the same turnaround time when the runtime of the process are equal.

5. **For what types of workloads and quantum lengths does SJF deliver the same response times as RR?**

When running multiples short processes with short quantum lengths, SJF and RR should performe very similarly.

6. **What happens to response time with SJF as job lengths increase? Can you use the simulator to demonstrate the trend?**

When job lengths increase under SJF, the response time starts to increse aswell, since it will take longer for the scheduler to switch processes because the shortest job will take longer to complete.

```bash
$ ./scheduler.py -p SJF -l 100,200,300 -c | grep Average
  Average -- Response: 133.33  Turnaround 333.33  Wait 133.33

$ ./scheduler.py -p SJF -l 200,300,400 -c | grep Average
  Average -- Response: 233.33  Turnaround 533.33  Wait 233.33

$ ./scheduler.py -p SJF -l 500,700,800 -c | grep Average
  Average -- Response: 566.67  Turnaround 1233.33  Wait 566.67
```

7. **What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?**

As QL increase, the response times increase aswell, since it will take longer for the scheduler to "cycle" through all the processes, increasing the response time.

Worst Case Response Time = (N-1) * QL
