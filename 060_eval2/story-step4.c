#include "rand_story.h"


// add an option "-n" indicating no reuse of words
int main(int argc, char ** argv) {
  if (argc < 3 || argc > 4) {
    printErr("invalid input");
  }
    size_t mode = 0;
    char * name1 = NULL;
    char * name2 = NULL;
  if (argc == 4) {
    if (strcmp(argv[1], "-n") != 0) {
      printErr("invalid input, use'-n' to choose mode");
    }
    name1 = argv[2];
    name2 = argv[3];    
    mode = 1;
  } 
  if (argc == 3) {
    name1 = argv[1];
    name2 = argv[2];   
    mode = 0;
  }  
  FILE * f1 = safeOpen(name1, "r", NULL);
  catarray_t * catArr = readCat(f1);
  safeClose(f1);
  FILE * f2 = safeOpen(name2, "r", catArr); 
  char * text = readTxt(f2);  
  char * textParse = parseTxt(text, catArr, mode, f2);
  printf("%s", textParse);
  free(text);
  free(textParse);
  freeCat(catArr);
  safeClose(f2); 
	return EXIT_SUCCESS;
}

