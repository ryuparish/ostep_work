#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main() {
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    }

    else if (rc == 0) { 
        const char* arg1 = "/bin/ls";
        const char* arg2 = "fork.c";
        execl(arg1, arg2, (char*) NULL);
    }

    return 0;
}

// There are many different version of the exec call due to the fact that there are many different
// possible things you could want to do with it, such as opening a self made program at a 
// certain path or a terminal program that doesn't need one. Also the v versions allow of lots of
// arguments without having to put all of them in the function call ( in a list instead ).
