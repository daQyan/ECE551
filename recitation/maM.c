#include <stdio.h>
#include <stdlib.h>


// store the martix
struct matrix_tag { 
  double ** values; 
  size_t rows; 
  size_t columns;
};
typedef struct matrix_tag matrix_t;

// multiply two martix
// matrix_t * multiply(matrix_t * left, matrix_t * right){
// //write this
  
// }

matrix_t * readMatrix(const char * filename) {
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        perror("Could not open file");
        exit(EXIT_FAILURE);
    }
    char *curr = NULL;
    size_t linecap;
    matrix_t * matrix = malloc(sizeof (*matrix));
    getline(&curr, &linecap, f);
    matrix->rows = atoi(curr);
    getline(&curr, &linecap, f);
    matrix->columns = atoi(curr);
    matrix->values = malloc(matrix->rows * sizeof (*matrix->values));
    for(size_t i = 0; i < matrix->rows; ++i) {
        matrix->values[i] = malloc(matrix->columns * sizeof(**matrix->values));
        for(size_t j = 0; j < matrix->columns; ++j) {
            getline(&curr, &linecap, f);
            if (curr[0] == 10) {
                printf("%c", curr[0]);
            }
            matrix->values[i][j] = atof(curr);           
        }
    }
    free(curr);
    if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        exit(EXIT_FAILURE);
    }
    return matrix;
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


// Free the given matrix
void freeMatrix(matrix_t * matrix) {
    for(size_t i = 0; i < matrix->rows; ++i) {
        free(matrix->values[i]);
    }
    free(matrix->values);
    free(matrix);
}

int main(int argc, char ** argv) {
    matrix_t * x = readMatrix(argv[1]);
    printMatrix(x);
}



