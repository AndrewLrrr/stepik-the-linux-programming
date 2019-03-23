#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int counter = 0;

int numbers_counter(int fd)
{
    char buf[4096];
    int bytes = read(fd, buf, sizeof(buf));
    buf[bytes] = '\0';
    counter += atoi(buf);

    return bytes;
}

int main()
{
    int open_flags = O_NONBLOCK | O_RDONLY;
    int fd1 = open("./in1", open_flags);
    int fd2 = open("./in2", open_flags);

    if (fd1 == -1 || fd2 == -1) {
        printf("Error with opening pipes\n");
        return 0;
    }

    while (1) {
        fd_set fds;
        int maxfd;

        FD_ZERO(&fds);
        FD_SET(fd1, &fds);
        FD_SET(fd2, &fds);

        maxfd = fd1 > fd2 ? fd1 : fd2;

        int result = select(maxfd + 1, &fds, NULL, NULL, NULL);

        if (result > -1) {
            if (FD_ISSET(fd1, &fds)) {
                int bytes = numbers_counter(fd1);
                if (bytes == 0) {
                    FD_CLR(fd1, &fds);
                    close(fd1);
                }
            }
            if (FD_ISSET(fd2, &fds)) {
                int bytes = numbers_counter(fd2);
                if (bytes == 0) {
                    FD_CLR(fd2, &fds);
                    close(fd2);
                }
            }
        } else {
            printf("%d\n", counter);
            return 0;
        }
    }
}
