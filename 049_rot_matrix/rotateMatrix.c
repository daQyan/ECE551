#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>    
#define LINESIZE 12

// char* array[] readInput(FILE *f) {

// }


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "wrong input: %s\n", argv[0]); // error 1
        exit(EXIT_FAILURE);
    }    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "fail to open file %s\n", argv[1]); // error2
		exit(EXIT_FAILURE);
    }    

    // store input into matrix

    int num = 0;
    char lineTb[11][LINESIZE] = {0};
    while ((fgets(lineTb[num], LINESIZE, f)) != NULL) {
        
        if (strchr(lineTb[num], '\n') == NULL) {
            fprintf(stderr, "line is too long \n"); // error3
            exit(EXIT_FAILURE);
        }
        if (lineTb[num][10] != '\n') {
            fprintf(stderr, "line is too short \n"); // error4
            exit(EXIT_FAILURE);
        }        
        // printf("%s",lineTb[num]);
        num++;
    }
    if (num < 10) {
        fprintf(stderr, "too few lines\n");
        exit(EXIT_FAILURE);
    }
    if (num > 10) {
        fprintf(stderr, "too many lines\n");
        exit(EXIT_FAILURE);
    }   
  
    
    // rotate matrix
    char lineRtb[11][LINESIZE] = {0};

    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            lineRtb[i][j] = lineTb[9-j][i];
        }
        fprintf(stdout,"%s\n", lineRtb[i]);
    }
    
    return EXIT_SUCCESS;
}
