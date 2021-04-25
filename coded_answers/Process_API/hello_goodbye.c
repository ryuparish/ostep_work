#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    else if (rc == 0) {
        printf("Hello I am a child (pid: %d)\n" , getpid());
    }

    else {
        int rc_wait = wait(NULL);
        // sleep(1) also works 
        printf("Goodbye I am the parent (pid: %d)\n", getpid());
    }
    return 0;
}


