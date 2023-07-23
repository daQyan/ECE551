
#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
    if (power(x, y) != expected_ans)
    {
        printf("opps");
        exit(EXIT_FAILURE);
    }
    else{
        printf("nice \n");
    }
}


int main()
{
    run_check(0, 0, 1);
    run_check(1, 99, 1);
    run_check(88, 0, 1);
    run_check(2, 2, 4);
    run_check(2, 1, 2);
    run_check(3, 3, 27);
    run_check(2.2, 3.1, 8);
    run_check(12345678, 1, 12345678);
    return EXIT_SUCCESS;
    
}
