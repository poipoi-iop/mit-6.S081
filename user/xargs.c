// implementation of a user-level program xargs

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"
#define MAX_ARG_LEN 512

int main(int argc, char *argv[]) {
    // if the number of args is lower than 2
    // the command to be executed
    char *cmd;
    if (argc < 2) {
        // the command is echo by default
        cmd = "echo";
    } else {
        cmd = argv[1];
    }
    // the args of the command to be executed
    char *argvs[MAXARG];
    int argv_curr = 0;
    memset(argvs, 0, MAXARG * sizeof(char *));
    argvs[argv_curr++] = cmd;

    // the buf containing args from pipe
    char buf[MAX_ARG_LEN];
    memset(buf, '\0', MAX_ARG_LEN * sizeof(char));


    int pid = fork();
    if (pid == 0) {
        // copy the original args of the command into argvs
        if (argc > 2) {
            for (int i = 2; i < argc; i++) {
                argvs[argv_curr++] = argv[i];
            }
        }
        // get the argv from standard input
        // read the input character by character
        char c = '\0';
        int counter = 0;
        // show the string which we are reading
        char *p = buf;
        while (read(0, &c, sizeof(c))) {
            if (c == '\n') {
                buf[counter++] = '\0';
                argvs[argv_curr++] = p;
                p = buf + counter;
            } else if (c == '\0') {
                buf[counter] = c;
                argvs[argv_curr] = p;
            } else {
                buf[counter++] = c;
            }
        }
        exec(cmd, argvs);
        printf("exec failed!");
        exit(1);
    } else {
        wait((int *)0);
    }
    exit(0);
}