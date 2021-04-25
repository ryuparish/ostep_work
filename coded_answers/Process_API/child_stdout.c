#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int cp = fork();
    if (cp < 0) {
        fprintf(stderr, "fork failed");
        exit(1);
    }

    else if (cp == 0) {
        close(STDOUT_FILENO);
        printf("I am a child. (pid:%d)\n", getpid());
    }
    return 0;
}

// Trying to use print after closing the STDOUT_FILENO (the terminal output) will just result in nothing being printed and nothing happening
