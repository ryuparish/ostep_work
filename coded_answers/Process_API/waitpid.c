#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    printf("I am the parent (pid:%d)\n", (int) getpid());
    int rc = fork(), wstatus;
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) {
        printf("I have been born. (pid:%d)\n", (int) getpid());
    }
    else {
        pid_t rc_waitpid = waitpid(-1, &wstatus, WCONTINUED);
        printf("Whew, my child is very large. I am the parent (pid:%d) (rc_waitpid:%d)\n", (int) getpid(), rc_waitpid);
    }
    return 0;
}


// When wait is used by the parent, the return value is the child's pid. When used by the child process, the child will wait until the parent process finishes, then returns a value of -1.
// Waitpid can be useful when trying to time things correctly with the child process or MANY child processes. It can also tell you lots of information about the exit status and other things about
// the child processes that could prove difficult otherwise.
//
// When a child completes successfully, it looks like it sends back a signal of WCONTINUED to the original mother program. 
