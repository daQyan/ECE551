#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

// abstract the error checking function
void printErr(char * str) {
  fprintf(stderr, "Error: %s!\n", str);
  exit(EXIT_FAILURE);
}
// abstract the null checker
void checkNull(void * target, char * str) {
  if (target == NULL) {  
    printErr(str);
  }
}

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE *f = fopen(filename, "r");
  checkNull(f, "no file");  
  counts_t *c = createCounts();
  char* line = NULL;
  size_t sz;
  while (getline(&line, &sz, f) >= 0) {
    // check null
    char * tmp = NULL;                            // replace the '\0' with '\n'
    if ((tmp = strstr(line, "\n"))) {             // or use: line[len - 1] = '\0'
      *tmp = '\0';
    }
    char * val = lookupValue(kvPairs, line);
    addCount(c, val);
  }  
  free(line); // freeeeeeee!
  if (fclose(f) != 0) {  // close the file !!!!! !! again !! youtmcuole
    printErr("not close file");
  }
  return c;
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    printErr("not enough files");
  }
  for (size_t i = 1; i < argc-1; i++) {
    if (argv[i] == NULL) {
    printErr("no file");
    }
  }
  kvarray_t *kv = readKVs(argv[1]);
  for (size_t i = 2; i < argc; i++) {
    counts_t *c = countFile(argv[i], kv);
    char * outName = computeOutputFileName(argv[i]);
    FILE *f = fopen(outName, "w");
    checkNull(f, "no file");
    printCounts(c, f);    
    free(outName);
    if (fclose(f) != 0) {  // close the file !!!!! !! again !! youtmcuole
      printErr("not close file");
    }
    freeCounts(c);
  }
  freeKVs(kv);
  return EXIT_SUCCESS;
}
