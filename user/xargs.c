#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/param.h"

int main(int argc, char *argv[]){
	char buf[512], *newline;
	char *nargv[MAXARG];

	nargv[0] = argv[1];
	nargv[1] = argv[2];
	char *cmd = malloc(strlen(argv[1]));
	strcpy(cmd, argv[1]);
	// command = nargv[0], missunderstanding for argv[1] + argv[2]

	int count = 0; 
	int n = 0;
	newline = "";
	if (fork() == 0){
		while(read(0, buf, 1) != 0){ // read from I/O or pipes...
			if (buf[n] == '\n'){
				*newline++ = 0;
				nargv[2] = newline;
				exec(cmd, nargv);
				newline -= count;
			} else {
				count += 1;
				memmove(newline, &buf[n], 1);
				newline++;  // buf = newline
			}
			n += 1;
		}

	} else{
		wait(0);
	}
	exit(0);
}