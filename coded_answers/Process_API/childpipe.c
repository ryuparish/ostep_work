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

    pid_t cp[2];
    cp[0] = fork();
    if (cp[0] == -1) {
        fprintf(stderr, "fork failed");
        exit(1);
    }

    // First child process (writer)
    else if (cp[0] == 0) {
        
        // Close the read end of the pipe 
        close(pipefd[0]);
        printf("About to write!\n");
        dup2(pipefd[1], STDOUT_FILENO);


        // Close the write of the pipe since we are done writing 
        close(pipefd[1]);

        // Print and have the message be sent to the other child process
        printf("UNG!");

    }

    else {
        cp[1] = fork();

        if (cp[1] < 0) {
            perror("fork");
            exit(1);
        }

        // Second child process (reader)
        else if (cp[1] == 0) {
            
            // Close the write end of the pipe
            close(pipefd[1]);

            // Change the input file descriptor to be the pipe with the message in it
            dup2(pipefd[0], STDIN_FILENO);

            // Making a mailbox to put the message into
            char buf[BUFSIZ];

            // Reading the message out of the pipe 
            printf("About to read!\n");
            read(STDIN_FILENO, &buf, BUFSIZ);
            close(pipefd[0]);

            // Echoing the message into the terminal
            printf("Message from other child: %s\n", buf);
        }

        // Parent just return 0 for success
        int cp_wait1 = waitpid(cp[0], NULL, 0);
        int cp_wait2 = waitpid(cp[1], NULL, 0);
        return 0;
    }
}


// According to the events that happen in this program, the first child writes, then the second child reads in the message written, in that order 
