#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

int find_process_in_pid(const pid_t pid, const char *needle) {
    char path[100];
    char buffer[1024];
    sprintf(path, "/proc/%d/stat", pid);
    FILE *fd = fopen(path, "r");

    if (fd == NULL) {
        perror("fd");
        printf("Error path: %s\n", path);
        exit(EXIT_FAILURE);
    }

    int status = 0;

    size_t size = fread(buffer, sizeof(char), sizeof(buffer), fd);
    if (size > 0 && strstr(buffer, needle) != NULL) {
        status = 1;
    }

    fclose(fd);

    return status;
}

int main()
{
    DIR *dir;
    struct dirent *ent;

    int counter = 0;
    char needle[] = "genenv";
    if ((dir = opendir("/proc/")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            pid_t pid = atoi(ent->d_name);
            if (pid > 0)
                counter += find_process_in_pid(pid, needle);
        }
        closedir(dir);
    } else {
        perror("dir");
        exit(EXIT_FAILURE);
    }

    printf("%d\n", counter);
    return 0;
}
