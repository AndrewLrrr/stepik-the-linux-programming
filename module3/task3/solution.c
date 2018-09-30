#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>


pid_t get_parent_pid(const pid_t pid)
{
    pid_t ppid = pid;
    char path[100];
    char buffer[1024];
    sprintf(path, "/proc/%d/stat", pid);
    FILE *fd = fopen(path, "r");

    if (fd == NULL) {
        perror("fd");
        printf("Error path: %s\n", path);
        exit(1);
    }

    size_t size = fread(buffer, sizeof(char), sizeof(buffer), fd);
    if (size > 0) {
        int counter = 0;
        char *pch = strtok(buffer, " ");
        while (counter != 2) {
            pch = strtok(NULL, " ");
            counter++;
        }
        ppid = atoi(strtok(NULL, " "));
    }

    fclose(fd);

    return ppid;
}

void print_process_parents(char *inp)
{
    pid_t pid = atoi(inp);
    printf("%d\n", pid);

    while (true) { ;
        pid = get_parent_pid(pid);
        printf("%d\n", pid);
        if (pid == 1) {
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    print_process_parents(argv[1]);
    return 0;
}
