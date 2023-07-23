#include <stdio.h>
#include <stdlib.h>


size_t  maxSeq(int * array, size_t n) {
    if (n <= 1)
    {
        return n;
    }
    size_t max = 1;
    size_t max_temp = 1;
    for (int i = 0; i < n-1; i++)
    {
        if (array[i] < array[i+1]) {
            max_temp++;
        }
        else if (max_temp > max) {
            max = max_temp;
            max_temp = 1;  
        }
        else{
            max_temp = 1;  
        }
      
    }
    if (max_temp > max) {
        max = max_temp;
    }
    return max;
}