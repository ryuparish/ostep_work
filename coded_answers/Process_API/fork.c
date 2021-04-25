#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    printf("I am the parent (pid:%d). Unng! I am having a child\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0) {
        printf("I have been born. (pid:%d)\n", (int) getpid());
    }
    else {
        int rc_wait = wait(NULL);
        printf("Whew, my child is very large. I am the parent (pid:%d) (rc_wait:%d)\n", (int) getpid(), rc_wait);
    }
    return 0;
}


    
