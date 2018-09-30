#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    pid_t pid;

    switch (pid = fork()) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            chdir("/");

            setsid();

            printf("%d\n", getpid());

            close(STDIN_FILENO);
            close(STDOUT_FILENO);
            close(STDERR_FILENO);

            while (1) {
                // Do nothing
            }
    }
    return 0;
}
