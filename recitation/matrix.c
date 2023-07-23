#include <stdio.h>
#include <stdlib.h>

// store the martix
struct matrix_tag
{
    double **values;
    size_t rows;
    size_t columns;
};
typedef struct matrix_tag matrix_t;

// multiply two martix
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

// read two martix from two files
matrix_t *readMatrix(const char *filename) 
{
    FILE *f = fopen(filename, "r");
    if (f == NULL)
    {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }
    char *curr = NULL;
    size_t linecap;
    matrix_t *matrix = malloc(sizeof(*matrix));
    getline(&curr, &linecap, f);
    matrix->rows = atoi(curr);
    getline(&curr, &linecap, f);
    matrix->columns = atoi(curr);
    matrix->values = malloc(matrix->rows * sizeof(*matrix->values));
    for (size_t i = 0; i < matrix->rows; ++i)
    {
        matrix->values[i] = malloc(matrix->columns * sizeof(**matrix->values));
        for (size_t j = 0; j < matrix->columns; ++j)
        {
            getline(&curr, &linecap, f);
            matrix->values[i][j] = atof(curr);
        }
    }
    free(curr);
    if (fclose(f) != 0)
    {
        perror("Failed to close the input file!");
        exit(EXIT_FAILURE);
    }
    return matrix;
}

// Print the given mtrix
void printMatrix(matrix_t *matrix)
{

    for (size_t row = 0; row < matrix->rows; row++)
    {
        for (size_t col = 0; col < matrix->columns; col++)
        {
            printf("%lf ", matrix->values[row][col]);
        }
        printf("\n");
    }
}

// Free the given matrix
void freeMatrix(matrix_t *matrix)
{
    for (size_t i = 0; i < matrix->rows; ++i)
    {
        free(matrix->values[i]);
    }
    free(matrix->values);
    free(matrix);
}

int main(int argc, char **argv)
{
    // write this
    //  EXIT_FAILURE
    if (argc != 3)
    {
        fprintf(stderr, "The input number is incorrect!\n");
        exit(EXIT_FAILURE);
    }

    matrix_t *matrix1;
    matrix1 = readMatrix(argv[1]);
    matrix_t *matrix2;
    matrix2 = readMatrix(argv[2]);

    matrix_t *result;
    result = multiply(matrix1, matrix2);
    freeMatrix(matrix1);
    freeMatrix(matrix2);
    printMatrix(result);
    freeMatrix(result);
    return (EXIT_SUCCESS);
    // read two files and git two matrixs

    // multiply them
}