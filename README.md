# Modified-XV6
This repo contains the modified version of the xv6 operating system

- Added 2 system calls:
    1. syscount <mask> command [args] --> where command [args] is any other valid command in XV6.
    2. sigalarm(n, fn) --> then after every n  ”ticks” of CPU time that the program consumes, the kernel will cause application function fn  to be called. When fn  returns, the application will resume where it left off.
- Added 2 new scheduling policies:
    1. LBS: Implemented a preemptive lottery based scheduling policy that assigns a time slice to the process randomly in proportion to the number of tickets it owns. That is, the probability that the process runs in a given time slice is proportional to the number of tickets owned by it.
   2. MLFQ: Implemented a simplified preemptive MLFQ scheduler that allows processes to move between different priority queues based on their behavior and CPU bursts.
