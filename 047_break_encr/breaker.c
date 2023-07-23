#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// return frequency of each letter
int maxFreq(int tb[]) {
    int maxFreq = 0;
    for (int i = 0; i < 26; i++) {
        if (tb[i] > tb[maxFreq]) {
            maxFreq = i;
        }
    }    
    return (maxFreq + 22)%26;
}   

int getkey(FILE *f) {
    int key;
    int c; 
    int freqTable[26] = {0};
    int i = 0;
    while ((c = fgetc(f)) != EOF ) {
        if (isalpha(c)) {
            freqTable[tolower(c) - 'a']++;
        }        
    }

    key = maxFreq(freqTable);
    return key;
}      

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "wrong input: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }    
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "fail to open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
    }    
    int key = getkey(f);
    printf("%d\n", key);
    fclose(f);
    return EXIT_SUCCESS;
}
