#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    switch (pid = fork()) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            printf("C: Это процесс потомок! Мой PID: %d\n", getpid());
            printf("C: Мой родитель PID: %d\n", getppid());
            sleep(10);
            exit(0);
        default:
            printf("P: Это процесс родитель! Мой PID: %d\n", getpid());
            printf("P: PID потомка: %d\n", pid);
            printf("P: PID родителя: %d\n", getppid());
            printf("P: Ждем когда потомок вызовет exit\n");
            wait(0);
            printf("P: Выход!\n");
    }

    return 0;
}