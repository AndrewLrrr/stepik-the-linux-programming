#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>


void get_parent_pid(const pid_t pid, pid_t *ppid)
{
    char path[100];
    char buffer[1024];
    sprintf(path, "/proc/%d/stat", pid);

    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        perror("fd");
        printf("Error path: %s\n", path);
        exit(1);
    }

    read(fd, buffer, 1024);

    int counter = 0;
    char *pch = strtok(buffer, " ");
    while (counter != 2) {
        pch = strtok(NULL, " ");
        counter++;
    }
    *ppid = atoi(strtok(NULL, " "));

    close(fd);
}

void print_process_parents(char *inp)
{
    pid_t pid = atoi(inp);

    while (pid != 1) {
        if (pid == 0) {
            break;
        }
        printf("%d\n", pid);
        get_parent_pid(pid, &pid);
    }

    if (pid == 1) {
        printf("--------\n%d (init)\n", pid);
    } else {
        printf("--------\n%d (sched)\n", pid);
    }
}

int main(int argc, char *argv[])
{
    if (NULL == argv[1]) {
        printf("Specify process id\n");
        exit(1);
    }

    print_process_parents(argv[1]);

    return 0;
}