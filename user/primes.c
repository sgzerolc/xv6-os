#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RANGE 35

void newProcess(int p[2]){
    int buff[1];
    int c[2];
    pipe(c);

    close(p[1]);
    if (read(p[0], buff, 4) < 0){
        fprintf(2, "read error\n");
        exit(1);
    } //read from parent
    int prime = buff[0]; 
    printf("prime %d\n", prime);
    if (fork() == 0){
        newProcess(c); // the first number in the pipe is the prime
    } else {
        while(read(p[0], buff, 4) != 0){
            int n = buff[0];
        // printf("%d", n);
            if (n % prime != 0){write(c[1], &n, 4);}
            }
        close(c[1]);
        wait(0); 
        }
        exit(0);
}

int main(){
    int fds[2];
    int pid;
    pipe(fds);

    pid = fork();
    if (pid == 0) {
        newProcess(fds);
    } else {
        // feed the numbers into the pipeline.(Left end)
        for (int i = 2; i < RANGE; i++){
            if (write(fds[1], &i, 4) != 4){ // can't write the number into main process
                fprintf(2, "write error\n");
                exit(1);
            }
        }
        close(fds[1]);
        wait(0);       
        exit(0);
    }
    return 0;
}

