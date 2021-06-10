#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void eliminate(int*child,int* buffer, int* pipe, int* port){
    
    read(child[0], port, 4);
    int p = *child;
    printf("prime %d\n", p);

    for (int i = 1; i < 20;i++) {
        read(pipe[0], buffer, 4);
        int n = *(buffer + i);
        if (n % p != 0){
            write(child[1], &n, 4);            
            if (read(pipe[0], buffer, 4) == 0){
                if (fork() == 0){
                    eliminate(child, buffer+i, pipe, port+i);
                } else {
                    wait(0);
                }
            }
        } else {
            continue;
        }
    }

}

int 
main() {
    int p[2];
    int c[2];
    int buff[36];
    int trans[16];

    int start = 2;

    pipe(p);
    pipe(c);


    if (fork() == 0){
        read(p[0], buff, 4);
        if (buff[0] == start){
            if (fork() == 0){
                write(c[1], &start, 4);
                eliminate(c, buff, p, trans);
            } else {
                wait(0);
            }
        }
        exit(0);
    } else { //process: parent,main
        close(p[0]);
        for (int i = 2; i <= 35; i++) {
            write(p[1], &i, 4); //feed numbers
        }
        // wait(0);
        exit(0);
    }
}



