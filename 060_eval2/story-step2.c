#include "rand_story.h"

// read the file then parse and store the file in data structure
int main(int argc, char ** argv) {
  if (argc != 2)
    printErr("input should be two arguments");
  FILE * f = safeOpen(argv[1], "r", NULL);    // check file existence
  catarray_t * catArr = readCat(f);
  printWords(catArr);
  safeClose(f);
  freeCat(catArr);
  return EXIT_SUCCESS;
}



