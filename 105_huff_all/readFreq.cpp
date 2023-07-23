#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <fstream>


void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    std::cerr << "Error opening file:" << fname << std::endl;
    exit(EXIT_FAILURE);
  }  
  uint64_t * lst = new uint64_t[257]();   // 257 becuase of EOF
  int c = 0;    // type is int 
  while ((c = fgetc(f)) != EOF) {   
    ++lst[c];
  }
  ++lst[256];
  fclose(f);
  return lst;
}
