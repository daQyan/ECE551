#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  const char * suffix = ".counts";
  size_t len = strlen(inputName) + strlen(suffix) + 1;
  char * outName = malloc(len * sizeof(outName));
  strcpy(outName, inputName);
  strcat(outName, suffix);
  return outName;
}
