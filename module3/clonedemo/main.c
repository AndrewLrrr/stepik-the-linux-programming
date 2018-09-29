#define _GNU_SOURCE
#include <sched.h>  // clone
#include <stdio.h>  // printf
#include <unistd.h>  // usleep
#include <stdbool.h>  // true

#define STACK_SIZE 10000
char child_stack[STACK_SIZE+1];


int child(void *params)
{
    int c = 0;
    while (true) {
        usleep(100000);
        printf("child turn %d\n", c++);
    }
}

int main()
{
    int c = 0;
    int result = clone(child, child_stack+STACK_SIZE, CLONE_PARENT, 0);
    printf("clone result = %d\n", result);
    while (true) {
        usleep(100000);
        printf("parent turn %d\n", c++);
    }
}