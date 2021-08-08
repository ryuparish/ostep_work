#include <stdlib.h>
#include <stdio.h>

int main() {
    int* vector;
    int limit = 0;
    vector = malloc(sizeof(int));
    for (size_t i = 0; i < 100; ++i){
        printf("\nOkay! Enter 100 numbers to add to the array (or -1 to stop): ");
        scanf("%d", (vector + i));
        if (vector[i] == -1) {
            break;
        }
        printf("\nYou entered: %d\nand it was added to the vector!", vector[i]);
        // ALWAYS reallocate the size of a POINTER TO AN INTEGER. NOT JUST AN INTEGER! *INT > INT. WE ARE USING *INTS in each part of the list since this is dynamically allocated.
        vector = realloc(vector, (i + 1) * sizeof(int*));
        limit++;
    }

    printf("\nHere is the vector you created: ");
    for (int i = 0; i < limit ; ++i){
        printf("% ", vector[i]);
    }
    free(vector);
    return 0;
}
