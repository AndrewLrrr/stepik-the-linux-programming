#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

char *concat(const char *s1, const char *s2, const char *s3)
{
    char *buffer = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1);

    if (NULL == buffer) {
        printf("String concatenation was failed\n");
        exit(1);
    }

    strcpy(buffer, s1);
    strcat(buffer, s2);
    strcat(buffer, s3);
    return buffer;
}

char *get_parent_pid(char const *current)
{
    int counter = 0;
    char buf[1024];
    char *pch;
    char *path = concat("/proc/", current, "/stat");

    int fd = open(path, O_RDONLY);

    if (fd == -1) {
        perror("fd");
        printf("Error path: %s\n", path);
        free(path);
        exit(1);
    }

    read(fd, buf, 1024);

    pch = strtok(buf, " ");
    while (counter != 3) {
        pch = strtok(NULL, " ");
        counter++;
    }

    char *cur = malloc(strlen(pch));
    strcpy(cur, pch);

    free(path);

    return cur;
}

void print_process_parents(char *pid)
{
    char *current = pid;

    while (strcmp(current, "1") != 0) {
        if (strcmp(current, "0") == 0) {
            break;
        }
        printf("%s\n", current);
        char *ppid = get_parent_pid(current);
        strcpy(current, ppid);
        free(ppid);
    }

    if (strcmp(current, "1") == 0) {
        printf("--------\n%s (init)\n", current);
    } else {
        printf("--------\n%s (sched)\n", current);
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