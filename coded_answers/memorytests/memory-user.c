#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int x = atoi(argv[1]);
    int* array = (int*) malloc(x * sizeof(int));
    int* array_begin;
    int counter = 0;

    while(1){
        counter = counter % x;
        array[counter];
        counter++;
    }
    return 0;
}
        
        
    
