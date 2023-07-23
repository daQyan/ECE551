#include "rand_story.h"

// parse the story template by printing the story and replacing blanks with the word "cat"
int main(int argc, char **argv) {
  if (argc != 2)
    printErr("input should be two arguments");
  FILE * f = safeOpen(argv[1], "r", NULL);
  char * text = readTxt(f);
  char * textParse = parseTxt(text, NULL, 0, f);
  printf("%s", textParse);
  free(text);
  free(textParse);
  safeClose(f);
	return EXIT_SUCCESS;
}
