#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    int pipefd[2];
    int pipefd2[2];
    struct timeval t;
    char* buf = "Here is the message.";
    // For the first pipe 
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // For the second pipe
    if (pipe(pipefd2) == -1) {
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
        // Variable for containing the other childs time
        suseconds_t child2time;
        
        // Close the read end of the first pipe 
        close(pipefd[0]);

        // Close the write end of the second pipe 
        close(pipefd2[1]);

        // Write into pipe the time 
        gettimeofday(&t, NULL);
        write(pipefd[1], &(t.tv_usec), sizeof(suseconds_t));

        // Test start here
        read(pipefd2[0], &child2time, sizeof(suseconds_t));
        gettimeofday(&t, NULL);
        printf("Child 2 Wrote at: %ld\nChild 1 Read at: %ld", child2time, (t.tv_usec));
        // Close the write of the pipe since we are done writing 
        close(pipefd[1]);
        printf("\nDone\n");
    }

    else {
        cp[1] = fork();

        if (cp[1] < 0) {
            perror("fork");
            exit(1);
        }

        // Second child process (reader)
        else if (cp[1] == 0) {
            
            // Close the write end of the first pipe
            close(pipefd[1]);

            // Close the read end of the second pipe
            close(pipefd2[0]);

            // Change the input file descriptor to be the pipe with the message in it
            dup2(pipefd[0], STDIN_FILENO);

            // Making a mailbox to put the message into
            suseconds_t prev_time;

            // Reading the message out of the pipe 
            read(STDIN_FILENO, &prev_time, sizeof(suseconds_t));

            // Test starts here
            gettimeofday(&t, NULL);
            write(pipefd2[1], &(t.tv_usec), sizeof(suseconds_t));

            close(pipefd[0]);
        }

        // Parent just return 0 for success
        int cp_wait1 = waitpid(cp[0], NULL, 0);
        int cp_wait2 = waitpid(cp[1], NULL, 0);
        return 0;
    }
}


// The time on average is about 70 microseconds to perform a context switch. But remember, we are:
// 1. Getting the time of the second child.
// 2. Writing the time into a pipe
// (3. Closing the pipe for the second child) If the kernel doesn't context switch immediately after the pipe writing.)
// 3. Reading in the time for the first child.
// 4. Getting the time of the first child.
