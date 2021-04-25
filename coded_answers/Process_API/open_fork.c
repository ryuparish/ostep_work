#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

int main () {
    printf("I am the parent (pid:%d)\n", (int) getpid());
    // Opening the file
    // STDOUT_FILENO is standardly set to be the terminal screen
    close(STDOUT_FILENO);
    open("./open_fork.out", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);

    // Then having a child by forking
    int rc = fork();
    if (rc < 0 ) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    else if (rc == 0) {
        char* myargs[3];
        myargs[0] = strdup("echo");
        myargs[1] = strdup("foo!");
        myargs[2] = NULL;
        execvp(myargs[0], myargs);
    }

    else {
        char* parentargs[3];
        parentargs[0] = strdup("echo");
        parentargs[1] = strdup("foo parent!");
        parentargs[2] = NULL;
        execvp(parentargs[0], parentargs);
    }
    return 0;
}


// For some reason, when writing concurrently to the same file, the parent seems to finish first.
// Perhaps the rc program is a slight bit longer to run and get the child running than it is
// to get the return value and for the parent to finish this program
