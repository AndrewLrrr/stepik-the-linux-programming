#include <stdio.h>
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
    strcat(buffer, " ");
    strcat(buffer, s2);
    return buffer;
}

int main(int argc, char *argv[])
{
    FILE *fp;
    int c, counter = 0;
    char *command = concat(argv[1], argv[2]);

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        pclose(fp);
        exit(-1);
    }

    do {
        c = fgetc(fp);
        if (c == '0') counter++;
    } while (c != EOF); // Пока не конец файла

    pclose(fp);

    printf("%d\n", counter);

    return 0;
}
