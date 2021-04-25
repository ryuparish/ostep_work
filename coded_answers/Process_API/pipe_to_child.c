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
        // Close writer end of the pipe 
        close(pipefd[1]);
        

        // Change the input file descriptor to be the pipe with the message in it
        dup2(pipefd[0], STDIN_FILENO);

        // Making a mailbox to put the message into
        char mailbox[sizeof(buf)];
        read(STDIN_FILENO, &mailbox, sizeof(buf));
        close(pipefd[0]);

        execlp("echo", mailbox, NULL);
    }

    int cp2 = fork();
    if (cp2 < 0) {
        perror("fork");
        exit(1);
    }

    // Second child process (writer)
    else if (cp2 == 0) {
        printf("Entered the second child");
        
        // Close the read end of the pipe 
        close(pipefd[0]);
        write(pipefd[1], buf, sizeof(buf));

        close(pipefd[1]);
    }

    // Parent just return 0 for success
    int cp_wait = wait(NULL);
    return 0;
}
