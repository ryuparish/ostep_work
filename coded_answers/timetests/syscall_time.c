#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main() {
    struct timeval time;
    suseconds_t microtime1, microtime2; 
    char buf[BUFSIZ];
    printf("Before and after (stacked on top) : ");
    gettimeofday(&time, NULL);
    microtime1 = time.tv_usec;
    read(STDIN_FILENO, NULL, 0);
    gettimeofday(&time, NULL);
    microtime2 = time.tv_usec;
    printf("Here is the first time: %ld\n", microtime1);
    printf("Here is the second time: %ld\n", microtime2);
    return 0;
}

// On average, it is about 5 microseconds
