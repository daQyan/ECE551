#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void sortPrint(FILE *f) {

  if (f == NULL) {
    perror("Could not open the file");
    exit(EXIT_FAILURE);
  }

  char **lines = NULL;
  char *lineCurr = NULL;
  size_t sz;
  size_t len = 0;
  while (getline(&lineCurr, &sz, f) >= 0) {
    lines = realloc(lines, (len+1) * sizeof(*lines));
    lines[len] = lineCurr;
    lineCurr = NULL;
    len++;
  }
  free(lineCurr);
  sortData(lines, len);

  for (size_t i = 0; i < len; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);   
}

int main(int argc, char ** argv) {  
  // no arguments
  if (argc == 1) {
    FILE * f = stdin;                             //argv[1] 
    sortPrint(f);    
  } 
  else {                                          //1 or more arguments
    for (size_t i = 1; i < argc; i++) {
      FILE *f = fopen(argv[i], "r");              // "r" instead of 'r'
      sortPrint(f);
      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }    
    }

    return EXIT_SUCCESS;
  }
}