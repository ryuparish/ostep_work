#include <stdlib.h>
#include <stdio.h>

int main() {
    int* data;
    data = (int*) malloc(100 * sizeof(int));
    free(data[45]);
    return 0;
}
