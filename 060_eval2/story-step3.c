#include "rand_story.h"


// step3: 1) randomly choose a word from the named category to replace each blank and
// 2) support references to previously used words.

int main(int argc, char  ** argv) {
  if (argc != 3) {
    printErr("invalid input");
  } 
  FILE * f1 = safeOpen(argv[1], "r", NULL);  
  catarray_t * catArr = readCat(f1);
  safeClose(f1);    

  FILE * f2 = safeOpen(argv[2], "r", catArr); 
  char * text = readTxt(f2);
  char * textParse = parseTxt(text, catArr, 0, f2);
  printf("%s", textParse);
  free(text);
  free(textParse);
  freeCat(catArr);
  safeClose(f2);
	return EXIT_SUCCESS;
}


