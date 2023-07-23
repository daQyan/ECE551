#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"
counts_t * createCounts(void) {
  counts_t *c = malloc(sizeof(*c));
  c->countArray = NULL;
  c->numArray = 0;
  c->numUnknown = 0;
  return c;
  // cName->countArray = realloc(cName->countArray, cName->numArray*sizeof(*cName->countArray));
  // cName->countArray
}

void addNewOne(counts_t *c, size_t num, const char *name) {
  c->countArray = realloc(c->countArray, num*sizeof(*c->countArray));  
  one_count_t *cOne = malloc(sizeof(*cOne));
  size_t len = strlen(name)+1;
  cOne->strCount = malloc(len * sizeof(*cOne->strCount));
  strcpy(cOne->strCount, name);
  // cOne->strCount[len] = '\0';   // already have '\0' in str name
  cOne->numCount = 1;  
  c->countArray[num-1] = cOne;
}

void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->numUnknown++;
    return; // !!!
  }  
  for (size_t i = 0; i < c->numArray; i++) {
    if (strcmp(c->countArray[i]->strCount, name) == 0) {
      c->countArray[i]->numCount++;
      return;
    }    
  }
  c->numArray++;
  addNewOne(c, c->numArray, name);
}

void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->numArray; i++) {
    // one_count_t *curr = c->countArray[i];
    fprintf(outFile, "%s: %ld\n", c->countArray[i]->strCount, c->countArray[i]->numCount);
  }
  if (c->numUnknown != 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->numUnknown);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->numArray; i++) {
    free(c->countArray[i]->strCount);
    free(c->countArray[i]);
  }
  free(c->countArray);
  free(c);
}
