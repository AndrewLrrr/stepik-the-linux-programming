#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int opchar = 0;
    int optindex = 0;
    int has_correct_option = 0;
    int has_incorrect_option = 0;

    struct option opts[] = {
            {"query",                  required_argument, 0, 'q'},
            {"longinformationrequest", no_argument,       0, 'i'},
            {"version",                no_argument,       0, 'v'},
            {0,                        0,                 0, 0},
    };

    while ((opchar = getopt_long(argc, argv, "vq:i", opts, &optindex)) != -1) {
        switch (opchar) {
            case 'q':
                has_correct_option++;
                break;
            case 'i':
                has_correct_option++;
                break;
            case 'v':
                has_correct_option++;
                break;
            case '?':
                has_incorrect_option++;
                break;
        }
    }

    if (has_incorrect_option > 0) {
        printf("-\n");
    } else {
        printf("+\n");
    }

    return 0;
}
