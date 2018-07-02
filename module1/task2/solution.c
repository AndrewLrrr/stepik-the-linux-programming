#include <stddef.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

char *concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char *argv[])
{
    int (*multiplier)(int);

    int num = (int) strtol(argv[3], (char **)NULL, 10);

    void *hdl = dlopen(concat("./", argv[1]), RTLD_LAZY);

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

    return 0;
}