#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define RANGE 35

int main(){
    int fds[2];
    int pid;
    //expr1
    int cid;
    int buff[1];
    int cbuff[1];
    int prime;
    int test;
    int cds[2];

    pipe(fds);
    //expr1
    pipe(cds);

    pid = fork();
    if (pid == 0) {
        prime = 2; //magic word
        while(read(fds[0], buff, 4) != 0){
            test = buff[0];
            cid = fork();
            if (cid == 0){
                if (test % prime == 0){exit(0);}
                else {
                    prime = test;
                    write(cds[1], &prime, 4);
                }
            }else{
                read(cds[0], cbuff, 4);
                printf("prime: %d\n", cbuff[0]);
            }
        }
        wait(0);

        exit(0); //remember to exit the process.
    } else {
        for (int i = 3; i < RANGE; i++){
            write(fds[1], &i, 4);
        }
        wait(0);
        exit(0);
    }
}
