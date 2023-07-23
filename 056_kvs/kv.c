#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

kvpair_t * getOneKv(char * line) {
  char * ptrE = strchr(line, '=');
  kvpair_t * kv = malloc(sizeof(*kv));
  size_t lenKey = ptrE - line;
  size_t lenVal = strlen(line) - lenKey - 2; // '=' & '\n'

  kv->key = strndup(line, lenKey);
  kv->value = strndup(ptrE+1, lenVal);
  // kv->key = malloc((lenKey+1) * sizeof(*kv->key));
  // kv->value = malloc((lenVal+1) * sizeof(*kv->value));
  // strncpy(kv->key, line, lenKey);
  // strncpy(kv->value, ptrE+1, lenVal);   
  
  kv->key[lenKey] = '\0';
  kv->value[lenVal] = '\0';
  return kv;
}

kvarray_t * readKVs(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    return NULL; // perror?
  }
  kvarray_t * kva = malloc(sizeof(*kva));
  char * line = NULL;
  size_t sz;
  size_t i = 0;
  kva->numKvpair = 0;
  kva->kvarray = NULL; // initialize!!!!!
  while (getline(&line, &sz, f) >= 0) {
    kva->numKvpair++;
    i++;
    kva->kvarray = realloc(kva->kvarray, i*sizeof(*kva->kvarray));
    // kva->kvarray[i] = malloc(sizeof(**kva->kvarray));
    kva->kvarray[i-1] = getOneKv(line); // pay attention to i   
    // free(line); // freeeeeee
    // line = NULL; 
  }
  free(line);
  fclose(f);  // !!!!!
  return kva;
}

void freeKVs(kvarray_t * pairs) {

  for (size_t i = 0; i < pairs->numKvpair; i++) {
    free(pairs->kvarray[i]->key);
    free(pairs->kvarray[i]->value);
    free(pairs->kvarray[i]);
  }
  // while (--pairs->numKvpair)
  // {
  //   free((*(pairs->kvarray))->key);
  //   free((*(pairs->kvarray))->value);        // the position changed after the while loop so the next free is invalid
  //   free(* pairs->kvarray);
  //   pairs->kvarray++;
  // }
  free(pairs->kvarray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->numKvpair; i++) {
    kvpair_t * curr = pairs->kvarray[i];
    printf("key = '%s' value = '%s'\n", curr->key, curr->value);
  }  
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->numKvpair; i++) {
    kvpair_t * curr = pairs->kvarray[i];    
    if (strcmp(curr->key, key) == 0) {
      return curr->value;
    }  
  }
  return NULL;
}
