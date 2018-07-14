#include <stdio.h>

int main()
{
    char name[100];
    printf("What is your name? __\n");
    gets(name);
    return printf("Hello %s\n", name);
}