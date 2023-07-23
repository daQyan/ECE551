#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_num) {
    if (maxSeq(array, n) != expected_num)
    {
        printf("opps\n");
        exit(EXIT_FAILURE);
    }
    else{
        printf("nice \n");
    }
}


int main(void) {
    int array1[] = {0};
    int array2[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9, 7};
    int array3[] = {1, 1};
    int array4[] = {-1, 1, 2};
    int *array5 = NULL;


    run_check(array1, 1, 1);
    run_check(array2, 11, 4);
    run_check(array3, 2, 1);
    run_check(array5, 0, 0);
    run_check(array4, 3, 3);



    return EXIT_SUCCESS;
    
}
