#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

char *concat(const char *s1, const char *s2)
{
    char *buffer = malloc(strlen(s1) + strlen(s2) + 1);

    if (NULL == buffer) {
        printf("String concatenation was failed\n");
        exit(1);
    }

    strcpy(buffer, s1);
    strcat(buffer, s2);
    return buffer;
}

int main(int argc, char *argv[])
{
    int (*multiplier)(int);

    if (NULL == argv[1]) {
        printf("Specify the shared library name\n");
        exit(1);
    }

    if (NULL == argv[2]) {
        printf("Specify function name\n");
        exit(1);
    }

    if (NULL == argv[3]) {
        printf("Specify function value\n");
        exit(1);
    }

    int num = (int) strtol(argv[3], (char **)NULL, 10);

    char *libname = concat("./", argv[1]);

    void *hdl = dlopen(libname, RTLD_LAZY);

    if (NULL == hdl) {
        printf("Library was not loaded\n");
        return 0;
    }

    multiplier = dlsym(hdl, argv[2]);

    if (NULL == multiplier) {
        printf("Library was not loaded\n");
        return 0;
    }

    printf("%d\n", (*multiplier)(num));

    free(libname);

    return 0;
}