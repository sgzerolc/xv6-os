#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int count = atoi(argv[1]);
    
    int i = 0;
    while (i < count) {
        sleep(1);
        i += 1;
    }
    
    exit(0);
}
