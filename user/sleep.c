// implementation for a user-level sleep program

#include "kernel/types.h"
#include "user/user.h"

// this program returns 1 to represent that there is an error, and 0 for no error

int main(int argc, char *argv[]) {
    // check if the number of arguments is 0
    if (argc <= 1) {
        printf("the \"sleep\" expects 1 argument, got %d\n", argc - 1);
        exit(1);
    }
    // normal situation
    // the ticks want to sleep
    int ticks = atoi(argv[1]);
    // use the system call sleep to implement
    sleep(ticks);

    exit(0);
}