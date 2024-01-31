// implementation of a user-level program ping-pong

#include "kernel/types.h"
#include "user/user.h"

int main() {
    int p[2];       // pipe
    pipe(p);

    int pid = fork();
    char c = '\0';
    if (pid == 0) {
        read(p[0], &c, 1);      // wait for the parent to ping
        printf("%d: received ping\n", getpid());
        write(p[1], &c, 1);
    } else {
        write(p[1], &c, 1);     // ping the child
        wait((int *)0);         // wait for the child to end
        read(p[0], &c, 1);
        printf("%d: received pong\n", getpid());
    }
    close(p[0]);
    close(p[1]);
    exit(0);
}