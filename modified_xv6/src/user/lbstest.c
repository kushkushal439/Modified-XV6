#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/riscv.h"
#include "user/user.h"
#pragma GCC push_options
#pragma GCC optimize ("O0") // Causing wierd errors of moving things here and there

void usless_work() {
    for (int i = 0; i < 1000 * 900000; i++) {
        asm volatile("nop"); // avoid compiler optimizing away loop
    }
}

void test0(){
    settickets(600000);// So that parent will get the higher priority and the forks can run at once
    printf("TEST 0\n"); // To check the randomness
    int prog1_tickets = 200;
    int prog2_tickets = 40;
    int prog3_tickets = 2;
    int prog4_tickets = 8000;
    printf("Child 1 has %d tickets.\nChild 2 has %d tickets\nChild 3 has %d tickets\nChild 4 has %d tickets\n",
           prog1_tickets, prog2_tickets, prog3_tickets, prog4_tickets);
    if (fork() == 0) {
        printf("Child 1 started\n");
        sleep(1);
        settickets(prog1_tickets);
        usless_work();
        printf("Child 1 exited\n");
        exit(0);

    }
    if (fork() == 0) {
        printf("Child 2 started\n");
        sleep(1);
        settickets(prog2_tickets);
        usless_work();
        printf("Child 2 exited\n");
        exit(0);
    }
    if (fork() == 0) {
        printf("Child 3 started\n");
        sleep(1);
        settickets(prog3_tickets);
        usless_work();
        printf("Child 3 exited\n");
        exit(0);
    }
    if (fork() == 0) {
        printf("Child 4 started\n");
        sleep(1);
        settickets(prog4_tickets);
        usless_work();
        printf("Child 4 exited\n");
        exit(0);
    }
    wait(0);
    wait(0);
    wait(0);
    wait(0);
    printf("The correct order should be ideally 4,2,1 and then 3.\n");

}

void test1(){
    printf("TEST1\n"); // To check the FCFS part of the implementation
    int tickets = 30; // To check for this finish times
    settickets(30); // So that now, the parent will always get the main priority to set up its children
    sleep(1); // So that this will have a different ctime than others. Ctime is not entirely very accurate

    printf("Child 1 started\n");
    if (fork() == 0) {
        settickets(tickets);
        usless_work();
        printf("Child 1 ended\n");
        exit(0);
    }
    sleep(1);
    printf("Child 2 started\n");
    if (fork() == 0) {
        settickets(tickets);
        usless_work();
        printf("Child 2 ended\n");
        exit(0);
    }
    sleep(1);
    printf("Child 3 started\n");
    if (fork() == 0) {
        settickets(tickets);
        usless_work();
        printf("Child 3 ended\n");
        exit(0);
    }
    wait(0);
    wait(0);
    wait(0);
    printf("The order should be 1,2 and then 3 since all tickets have same value\n");
}
int main() {
    test0();
    test1();
    printf("Finished all tests\n");

    return 0;
}


// #include "kernel/param.h"
// #include "kernel/types.h"
// #include "kernel/stat.h"
// #include "kernel/riscv.h"
// #include "user/user.h"
// #pragma GCC push_options
// #pragma GCC optimize ("O0") // Causing wierd errors of moving things here and there

// void usless_work() {
//     for (int i = 0; i < 1000 * 900000; i++) {
//         asm volatile("nop"); // avoid compiler optimizing away loop
//     }
// }


// void test0(){
//     settickets(600);// So that parent will get the higher priority and the forks can run at once
//     printf("TEST 0\n"); // To check the randomness
//     int prog1_tickets = 1;
//     int prog2_tickets = 4;
//     int prog3_tickets = 16;
//     int prog4_tickets = 8;
//     printf("Child 1 has %d tickets.\nChild 2 has %d tickets\nChild 3 has %d tickets\nChild 4 has %d tickets\n",
//            prog1_tickets, prog2_tickets, prog3_tickets, prog4_tickets);

//     if (fork() == 0) {
//         settickets(prog1_tickets);
//         printf("Child 1 started\n");
//         sleep(1);
//         usless_work();
//         printf("Child 1 exited\n");
//         exit(0);

//     }
//     if (fork() == 0) {
//         settickets(prog2_tickets);
//         printf("Child 2 started\n");
//         sleep(1);
//         usless_work();
//         printf("Child 2 exited\n");
//         exit(0);
//     }
//     if (fork() == 0) {
//         settickets(prog3_tickets);
//         printf("Child 3 started\n");
//         sleep(1);
//         usless_work();
//         printf("Child 3 exited\n");
//         exit(0);
//     }
//     if (fork() == 0) {
//         settickets(prog4_tickets);
//         printf("Child 4 started\n");
//         sleep(1);
//         usless_work();
//         printf("Child 4 exited\n");
//         exit(0);
//     }
//     wait(0);
//     wait(0);
//     wait(0);
//     wait(0);
//     printf("The correct order should be ideally 3,4,2,1.\n");

// }

// void test1(){
//     printf("TEST1\n"); // To check the FCFS part of the implementation
//     int tickets = 30; // To check for this finish times
//     settickets(30); // So that now, the parent will always get the main priority to set up its children
//     sleep(1); // So that this will have a different ctime than others. Ctime is not entirely very accurate

//     printf("Child 1 started\n");
//     if (fork() == 0) {
//         settickets(tickets);
//         usless_work();
//         printf("Child 1 ended\n");
//         exit(0);
//     }
//     printf("Child 2 started\n");
//     if (fork() == 0) {
//         settickets(tickets);
//         usless_work();
//         printf("Child 2 ended\n");
//         exit(0);
//     }
//     printf("Child 3 started\n");
//     if (fork() == 0) {
//         settickets(tickets);
//         usless_work();
//         printf("Child 3 ended\n");
//         exit(0);
//     }
//     wait(0);
//     wait(0);
//     wait(0);
//     printf("The order should be 4,3 and 2 then 1 since all tickets have same value\n");
// }
// int main() {
//     test0();
//     test1();
//     printf("Finished all tests\n");

//     return 0;
// }

// #pragma GCC pop_options