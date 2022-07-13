# Homework
## Simulation

1. **Run ./fork.py -s 10 and see which actions are taken. Can you predict what the process tree looks like at each step? Use the -c flag to check your answers. Try some different random seeds (-s) or add more actions (-a) to get the hang of it.**

```
a ---------- b
```

```
a ---------- b
    |------- c
```

```
a ---------- b
```

```
a ---------- b
    |------- d
```

```
a ---------- b
    |------- d
    |------- e
```

2. **One control the simulator gives you is the fork percentage, controlled by the -f flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., -a 100) and vary the fork percentage from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes? Check your answer with -c.**

When `fork_percentage` is low, the processes are much more likely to quit, make it harder for a complex tree structure to appear in the process hierarchy.
When `fork_percentage` is high, it's much more likely that a tree pattern will emerge in the process structure.

3. **Now, switch the output by using the -t flag (e.g., run ./fork.py-t). Given a set of process trees, can you tell which actions were taken?**

After running `./fork -s 1 -t` I can deduce that the following happened:

- a forked b
- a forked c
- c forked d
- a forked e
- c exited

4. **One interesting thing to note is what happens when a child exits; what happens to its children in the process tree? To study this, let’s create a specific example: ./fork.py -A a+b,b+c,c+d,c+e,c-. This example has process ’a’ create ’b’, which in turn creates ’c’, which then creates ’d’ and ’e’. However, then, ’c’ exits. What do you think the process tree should like after the exit? What if you use the -R flag? Learn more about what happens to orphaned processes on your own to add more context.**

https://en.wikipedia.org/wiki/Orphan_process

The orphaned process gets reassigned to the first process in the tree. When using the `-R` flag, the process gets reparented by the parent of the killed process.

5. **One last flag to explore is the -F flag, which skips intermediate steps and only asks to fill in the final process tree. Run ./fork.py -F and see if you can write down the final tree by looking at the series of actions generated. Use different random seeds to try this a few times.**

6. **Finally, use both -t and -F together. This shows the final process tree, but then asks you to fill in the actions that took place. By looking at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell? Try some different random seeds to delve into this question.**

I ran `./fork.py -F -t` which produced the tree:
```
a
└── b
    ├── c
    ├── d
    └── e
        └── f
```
This tree can be produced by a+b,b+c,b+d,b+e,e+f
