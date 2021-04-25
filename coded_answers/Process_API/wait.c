#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    printf("I am the parent (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) {
        int rp_wait = wait(NULL);
        printf("I have been born. (pid:%d) (rp_wait:%d)\n", (int) getpid(), rp_wait);
    }
    else {
        printf("Whew, my child is very large. I am the parent (pid:%d)\n", (int) getpid());
    }
    return 0;
}


// When wait is used by the parent, the return value is the child's pid. When used by the child process, the child will wait until the parent process finishes, then returns a value of -1.
