#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int pipefd[2];
    char* buf = "Here is the message.";
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int cp = fork();
    if (cp == -1) {
        fprintf(stderr, "fork failed");
        exit(1);
    }

    // First child process (reader)
    else if (cp == 0) {
        printf("Entered the first child");
    }

    int cp_wait = wait(NULL);
    return 0;
}
