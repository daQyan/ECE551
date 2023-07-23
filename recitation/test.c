#include <stdio.h>
#include <stdlib.h>

struct matrix_tag
{
    double **values;
    size_t rows;
    size_t columns;
};
typedef struct matrix_tag matrix_t;


matrix_t *multiply(matrix_t *left, matrix_t *right)
{
    // write this
    if (left->columns != right->rows)
    {
        fprintf(stderr, "wrong size!!");
        exit(EXIT_FAILURE);
    }
    matrix_t *result = malloc(sizeof(*result));
    result->rows = left->rows;
    result->columns = right->columns;
    result->values = malloc(result->rows * sizeof(*result->values));
    for (size_t i = 0; i < result->rows; i++)
    {
        result->values[i] = malloc(result->columns * sizeof(**result->values));
    }

    for (size_t resultRow = 0; resultRow < result->rows; resultRow++)
    {
        for (size_t resultColumn = 0; resultColumn < result->columns; resultColumn++)
        {
            double sum = 0;
            for (size_t k = 0; k < left->columns; k++)
            {
                sum += left->values[resultRow][k] * right->values[k][resultColumn];
            }
            result->values[resultRow][resultColumn] = sum;
            }
    }

    return result;
}

// Print the given mtrix
void printMatrix(matrix_t * matrix) {

    for (size_t row = 0; row < matrix->rows; row++) {
        for (size_t col = 0; col < matrix->columns; col++) {
            printf("%lf ", matrix->values[row][col]);
        }
        printf("\n");
    } 
} 


int main(int argc, char const *argv[])
{
    matrix_t *result = malloc(sizeof(*result));
    result->rows = 2;
    result->columns = 3;
    result->values = malloc(result->rows * sizeof(*result->values));
    for (size_t i = 0; i < result->rows; i++)
    {
        result->values[i] = malloc(result->columns * sizeof(**result->values));
    }
    result->values[0][0] = 1;
    result->values[0][1] = 2;
    result->values[0][2] = 1;
    result->values[1][0] = 1;
    result->values[1][1] = 2;
    result->values[1][2] = 1;

    matrix_t *result1 = malloc(sizeof(*result1));
    result1->rows = 3;
    result1->columns = 2;
    result1->values = malloc(result1->rows * sizeof(*result1->values));
    for (size_t i = 0; i < result1->rows; i++)
    {
        result1->values[i] = malloc(result1->columns * sizeof(**result1->values));
    }

    result1->values[0][0] = 1;
    result1->values[1][0] = 2;
    result1->values[2][0] = 1;
    result1->values[0][1] = 9;
    result1->values[1][1] = 9.9;
    result1->values[2][1] = 7;


    matrix_t * output = multiply(result, result1);

    printMatrix(output);

    // for (size_t row = 0; row < output->rows; row++) {
    //     for (size_t col = 0; col < output->columns; col++) {
    //         printf("%lf ", output->values[row][col]);
    //     }
    //     printf("\n");
    // }  
    
    
    return 0;
}
