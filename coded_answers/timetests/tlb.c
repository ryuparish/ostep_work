#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
// Going to move on from this one, I do not understand how to the averaging of the time (maybe a little bit), or the conversion to nanoseconds works here (I did not do it)

// Function from unistd.h to get the page size: sysconf(_SC_PAGESIZE);
int main(int argc , char* argv[]){
    if( argc < 3 ){
        printf("Usage: ./___ num_of_pages num_of_trials");
        exit(1);
    }

    // Initializing variables and getting the timeval ready
    size_t PAGESIZE = sysconf(_SC_PAGESIZE); // Maybe it is not guaranteed that this is split up into 4 bytes? We divide by sizeof(int) later on 
    size_t NUMPAGES = atoi(argv[1]);
    size_t trials = atoi(argv[2]);
    size_t ints_per_page = PAGESIZE / sizeof(int);
    int* pages;
    pages = (int*)calloc(PAGESIZE*NUMPAGES, sizeof(int));
    struct timeval t;
    suseconds_t before_time, after_time;
    
    // Loop through the pages and increment the counter by the size of the page to go from the first value of one page to the first value of the second page to the first value of the third page... and so on.
    // Q: I am unsure as to why we use the number of pages multiplied by the ints_per_page as the stopping point
    // A: The reason is, because you are addint the ints_per_page to the incrementer. If you only had NUMPAGES, the incrementer would shoot past it on the first go since you are adding ints_per_page to it
    long long total;
    gettimeofday(&t, NULL);
    before_time = t.tv_usec;
    for(int j = 0; j < trials; ++j){
        
        for(int i = 0; i < NUMPAGES * ints_per_page; i += ints_per_page){
            pages[i] += 1;
            gettimeofday(&t, NULL);
        }

    }
    gettimeofday(&t, NULL);
    after_time = t.tv_usec;
    double average_time = (after_time - before_time) / (NUMPAGES * trials);
    printf("Average: %f", average_time);

    return 0;
}
