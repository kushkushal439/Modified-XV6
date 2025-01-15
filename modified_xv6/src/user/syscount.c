// #include "../kernel/types.h"
// #include "../kernel/stat.h"
// #include "user.h"

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

const char* getname(int mask) {
    switch (mask) {
        case 1:  return "fork";
        case 2:  return "exit";
        case 3:  return "wait";
        case 4:  return "pipe";
        case 5:  return "read";
        case 6:  return "kill";
        case 7:  return "exec";
        case 8:  return "fstat";
        case 9:  return "chdir";
        case 10: return "dup";
        case 11: return "getpid";
        case 12: return "sbrk";
        case 13: return "sleep";
        case 14: return "uptime";
        case 15: return "open";
        case 16: return "write";
        case 17: return "mknod";
        case 18: return "unlink";
        case 19: return "link";
        case 20: return "mkdir";
        case 21: return "close";
        case 22: return "waitx";
        case 23: return "getSysCount";
        case 24 : return "sigalarm";
        case 25 : return "sigreturn";
        default: return "unknown";
    }
}

int main(int argc, char* argv[]) {
    // syscount <mask> command [args] is given.
    if (argc < 3) {
        fprintf(2, "Usage: syscount <mask> command [args]\n");
        exit(1);
    }
    int mask = atoi(argv[1]);
    int actmask = 0;
    while(actmask <= 31) {
        if (mask == (1 << actmask)) {
            break;
        }
        actmask++;
    }
    mask = actmask;
    if (mask == 32) {
        printf("Invalid mask\n");
        exit(1);
    }
    int pid = fork();
    if (pid < 0) {
        printf("fork failed\n");
        exit(0);
    }
    if (pid == 0) {
        exec(argv[2], argv + 2);
        printf("exec failed\n");
        exit(1);
    }
    else {
        wait(0);
        int count = getsyscount(mask);
        printf("PID %d called %s %d times\n", pid,getname(mask), count);
        exit(0);
    }
    // now shud reset the parent PCB array to 0
}

