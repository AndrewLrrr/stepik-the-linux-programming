#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // getpid
#include <string.h>  // strtok

static void get_process_parent_id(const pid_t pid, pid_t *ppid)
{
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
        *ppid = atoi(strtok(NULL, " "));
    }

    fclose(fd);
}

int main()
{
    pid_t pid = getpid();
    get_process_parent_id(pid, &pid);
    printf("%d\n", pid);
}