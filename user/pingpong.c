#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main () {
    int fds[2];
    int buff[1];
    int pid;

    // create a pipe, with two fds in fds[0]. fds[1].
    pipe(fds);

    pid = fork();
    if (pid == 0) {
        printf("%d: received ping\n", getpid());
        write(fds[1], "r", 1);
        exit(0);
    } else {
        read(fds[0], buff, 1);
        printf("%d: received pong\n", getpid());
        exit(0);
    }

}