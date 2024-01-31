// implementation of a user-level program primes

#include "kernel/types.h"
#include "user/user.h"

int main() {
    int left_p[2];       // left neighbor pipe
    pipe(left_p);

    // write numbers from 2 to 35  into the pipe
    for (int i = 2; i <= 35; i++) {
        write(left_p[1], &i, sizeof(i));
    }

    // the base number of this process
    int base = 0;
    while (1) {
        int pid = fork();
        if (pid == 0) {
            int right_p[2];     // right neighbor pipe
            pipe(right_p);
            // select the number that can be divided by base
            close(left_p[1]);
            int curr_num = read(left_p[0], &base, sizeof(base));
            // if the pipe is empty
            if (!curr_num) exit(0);
            printf("prime %d\n", base);
            while (read(left_p[0], &curr_num, sizeof(curr_num))) {
                if (curr_num % base != 0) {
                    // write to the right neighbor pipe
                    write(right_p[1], &curr_num, sizeof(curr_num));
                }
            }
            close(left_p[0]);
            left_p[0] = right_p[0];
            left_p[1] = right_p[1];
        } else {
            // wait for the child to end
            // close the write end to enable that the child can reach the end of pipe
            close(left_p[0]);
            close(left_p[1]);
            wait((int *)0);
            exit(0);
        }
    }

}