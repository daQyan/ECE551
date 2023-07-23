#include "rand_story.h"

// check if memory allocated successfully
void memCheck(void * mem) {
  if (mem == NULL) {
    printErr("Memory allocated failed");
  }
}

// open the file and check if it is successful
// meanwhile free the memory allocated by the firstly opened file if the second file failed opening
FILE * safeOpen(char * filename, char * mode, catarray_t * cat) {
  FILE * f = fopen(filename, mode);
  if (f == NULL) {
    perror("Open file failed"); 
    freeCat(cat);
    exit(EXIT_FAILURE);
  }
  return f;
}

// close the file and check if it is successful
void safeClose(FILE * f) {
  if (fclose(f)) {
    perror("Close file failed");    
    exit(EXIT_FAILURE);
  }
  return;
}

// abstract the error checking function
void printErr(char * str) {
  fprintf(stderr, "Error: %s!\n", str);
  exit(EXIT_FAILURE);
}

// free necessary things, save the time of free before exit failure
void freeHelper(char * blank, catarray_t * cat, category_t * used, char * txt, char * txtNew, FILE * f) {
  freeUsed(used);
  free(txt);
  free(txtNew);
  freeCat(cat);
  free(blank);
  safeClose(f);  
}

// check to see if the "_ _" follow the correct format
size_t checkUnderscore(char * ptr) {
  // if (ptr[1] == '_') { return 0; }
  if (ptr[1] == ':') { return 0; }
  char * us = strchr(ptr+1, '_');
  char * nextLine = strchr(ptr, '\n');
  if (us == NULL) { return 0; }
  if (nextLine != NULL && nextLine - us < 0) {
    return 0;
  }
  return 1;
}

// read the story text into the string "text" and return
char * readTxt(FILE * f) {
  // size_t isEmpty = 1;
  char * line = NULL;
  size_t sz = 0;
  char * text = strdup(""); 
  size_t len = 0;
  while (getline(&line, &sz, f) >= 0) {
    // isEmpty = 0;
    len += strlen(line);
    text = realloc(text, (len+1) * sizeof (*text));
    memCheck(text);
		strncat(text, line, strlen(line));
  }
  // // check if the file is empty
  // if (isEmpty) {
  //   printErr("empty file");
  // }
	free(line);
	text[len] = '\0';
  return text;
}

// parse the text, when meet _word_ format string, replace it with the selected new one
// put all of the parsed string together and store as a new string
char * parseTxt(char * txt, catarray_t * catArray, size_t mode, FILE* f) { 
	char * ptr = NULL;
	char * curr = txt;
  char * textNew = strdup(""); 
  size_t lenAll = 1;
  category_t * usedArr = initUsedArr();    // initialize the used array
	while (*curr != '\0') {
		ptr = strchr(curr, '_');
    if (ptr != NULL) {
      if (checkUnderscore(ptr) == 0) {
        freeHelper(NULL, catArray, usedArr, txt, textNew, f);
        printErr("invalid underscore format");
      }
      size_t len = ptr - curr;
      lenAll += len; 
      textNew = realloc(textNew, lenAll * sizeof(*textNew));
      memCheck(textNew);
      strncat(textNew, curr, len);
      curr = ptr + 1;
      ptr++;
      while (*ptr != '_') {
        ptr++;
      }
      // find the replace word
      size_t lenBlank = ptr-curr;
      char * blank = getBlank(curr, lenBlank);
      const char * replace = getSubt(blank, catArray, usedArr, txt, textNew, f);              // check before call chooseword
      addUsed(replace, usedArr);             
      lenAll += strlen(replace);
      textNew = realloc(textNew, lenAll * sizeof(*textNew));
      memCheck(textNew);
      strncat(textNew, replace, strlen(replace));
      // see if it is -n mode
      if (mode) {
        resizeCat(catArray, replace, blank, txt, textNew, f, usedArr);
      }
      free(blank);       
      curr = ptr + 1;
    }
    // read the last part of the text 
    if (strchr(curr, '_') == NULL) { // ptr is NULL?
      lenAll += strchr(curr, '\0') - curr;
      textNew = realloc(textNew, (lenAll+1) * sizeof(*textNew));
      memCheck(textNew);
      strncat(textNew, curr, strchr(curr, '\0') - curr);
      textNew[lenAll] = '\0';
      break;
    }
	}
  freeUsed(usedArr);
  return textNew;
}

// resize the catarray_t: eliminate the word just used 
void resizeCat(catarray_t * catArray, const char * replace, char * blank, char * txt, char * txtNew, FILE * f, category_t * used) {
  for (size_t i = 0; i < catArray->n; i++) {
    if (strcmp(blank, catArray->arr[i].name) == 0) {  
      if (catArray->arr[i].n_words == 0) {
        freeHelper(blank, catArray, used, txt, txtNew, f); 
        printErr("no more words for the name");
      }
      for (size_t j = 0; j < catArray->arr[i].n_words; j++) {
        if (strcmp(replace, catArray->arr[i].words[j]) == 0) {
          free(catArray->arr[i].words[j]);
          for (size_t z = j; z < catArray->arr[i].n_words-1; z++) {
            catArray->arr[i].words[z] = catArray->arr[i].words[z+1];
          }
          catArray->arr[i].words[catArray->arr[i].n_words-1] = NULL;
          free(catArray->arr[i].words[catArray->arr[i].n_words-1]);
          catArray->arr[i].n_words--;
          return;
        }
      }    
    }
  }
}

// check if the whole string is a valid digit
size_t checkDigit(char * name) {
  while (*name != '\0') {
    if(isdigit(*name)) {
      ++name; 
    } else {
      return 0;
    }
  }
  return 1;
}

// check if the catagory name has corresponding words left
void checkWordsLeft(char * blk, catarray_t * cat, category_t * used, char * txt, char * txtNew, FILE * f) {
  size_t hasName = 0;
  for (size_t i = 0; i < cat->n; i++) {
      if (strcmp(blk, cat->arr[i].name) == 0) {  
        hasName = 1;        
        if (cat->arr[i].n_words == 0) {
          freeHelper(blk, cat, used, txt, txtNew, f);  
          printErr("no more words for the name");
        }
        return;
      }
  }
  if (! hasName) {
    freeHelper(blk, cat, used, txt, txtNew, f);  
    printErr("no such name catagory");
  }
}

// get the word that should be replaced into
const char * getSubt(char * blk, catarray_t * cat, category_t * used, char * txt, char * txtNew, FILE * f) {
  if (cat == NULL) {
    return chooseWord(blk, cat);
  }
  if (checkDigit(blk)) {
    size_t num = atoi(blk);           
      if (num > 0) {
        if (num > used->n_words) {
          freeHelper(blk, cat, used, txt, txtNew, f);
          printErr("reference out of bound");
        }
        size_t index = used->n_words - num;
        return used->words[index];
      } else {
        checkWordsLeft(blk, cat, used, txt, txtNew, f);
        return chooseWord(blk, cat);
      }       
  } else {
    checkWordsLeft(blk, cat, used, txt, txtNew, f);
    return chooseWord(blk, cat);
  }
}

// add the already used word into the struct
void addUsed(const char * subt, category_t * arr) {
  arr->words = realloc(arr->words, (arr->n_words+1) * sizeof(*arr->words));
  memCheck(arr->words);
  arr->words[arr->n_words] = strdup(subt); 
  arr->n_words++;
}

// initialize the struct to store used words
category_t * initUsedArr() {
  category_t * used = malloc(sizeof(*used));
  memCheck(used); 
  used->name = NULL;
  used->words = NULL;
  used->n_words = 0;  
  return used;
}

// get the word in _blank_
char * getBlank(char * cur, size_t len) {
  char * blank = strdup("");
  blank = realloc(blank, (len+1) * sizeof(*blank));
  memCheck(blank);
  strncpy(blank, cur, len);
  blank[len] = '\0'; //
  return blank;
}

// free the used words struct 
void freeUsed(category_t * used) {
  if (used != NULL) {
    for (size_t i = 0; i < used->n_words; i++) {
    free(used->words[i]);
  }
  free(used->words);
  free(used);
  } 
}

// free the catarray_t related memory
void freeCat(catarray_t * cat) {
  if (cat != NULL) {
    for (size_t i = 0; i < cat->n; i++) {    
    for (size_t j = 0; j < cat->arr[i].n_words; j++) {
      free(cat->arr[i].words[j]);
    }
    free(cat->arr[i].name);
    free(cat->arr[i].words);
  }
  free(cat->arr);
  free(cat); 
  }
}

// check if the colon in the file follows the format
size_t checkColon(char * line) {
  if (strchr(line, ':') == NULL) { return 0; }
  // if (line[0] == ':') { return 0; }
  if (line[strlen(line)-2] == ':') { return 0; } 
  if (strchr(line, '\n') == NULL) { return 0; } 
  return 1;
}

// read from the file and store the words into a catarray_t 
catarray_t * readCat(FILE * f) {
  // size_t isEmpty = 1;
  catarray_t * catArray = malloc(sizeof(*catArray));    
  memCheck(catArray);
  char * line = NULL;
  size_t sz;
  catArray->n = 0;
  catArray->arr = NULL;
  while (getline(&line, &sz, f) >= 0) {
    // isEmpty = 0;
    if (checkColon(line) == 0) {
      freeCat(catArray);
      free(line);
      safeClose(f);
      printErr("invalid input file, check the colon");
    } 
    // get the name
    char * ptr = strchr(line, ':');
    size_t lenName = ptr-line;
    char * currName = strndup(line, lenName);
    currName[lenName] = '\0';
    // get the word
    size_t lenWord = strchr(line, '\n') - ptr - 1;
    char * currWord = strndup(ptr+1, lenWord);
    currWord[lenWord] = '\0';
    size_t notHasName = 1;
  if (catArray->n == 0) {
    notHasName = 0; 
    initArr(catArray, currName, currWord);
  } else {
    notHasName = addArr(catArray, currName, currWord);
  }  
  if (notHasName) {
    addNewArr(catArray, currName, currWord);
  }   
  currName = NULL;
  currWord = NULL;
  }
  // // check if the file is empty
  // if (isEmpty) {
  //   printErr("empty file");
  // }
  free(line);
  return catArray; 
}

// initialize the cat array
void initArr(catarray_t * catArray, char * currName, char * currWord) {
  catArray->arr = malloc(sizeof(*catArray->arr));
  memCheck(catArray->arr);
  catArray->arr[0].name = currName;
  catArray->arr[0].n_words = 1;
  catArray->arr[0].words = malloc(sizeof(*catArray->arr[0].words));
  memCheck(catArray->arr[0].words);
  catArray->arr[0].words[0] = currWord;
  catArray->n++;          
}

// add the word to the existing name catagory and update the num_words of the name
int addArr(catarray_t * catArray, char * currName, char * currWord) {
  for (size_t i = 0; i < catArray->n; i++) {
    if (strcmp(currName, catArray->arr[i].name) == 0) {  
      // check if the catagory name has the same word
      for (size_t j = 0; j < catArray->arr[i].n_words; j++) {
        if (strcmp(currWord, catArray->arr[i].words[j]) == 0) {
          free(currName);
          free(currWord);
          return 0;
        }
      }
      free(currName);       
      catArray->arr[i].n_words++;
      catArray->arr[i].words = realloc(catArray->arr[i].words, 
      catArray->arr[i].n_words * sizeof(*catArray->arr[i].words));
      memCheck(catArray->arr[i].words);
      catArray->arr[i].words[catArray->arr[i].n_words - 1] = currWord;     
      return 0;
    }
  }
  return 1;
}

// add the word to the according name catagory when there is a new name catagory
void addNewArr(catarray_t * catArray, char * currName, char * currWord) {
  catArray->arr = realloc(catArray->arr, (catArray->n+1)*sizeof(*catArray->arr)); //
  memCheck(catArray->arr);
  catArray->arr[catArray->n].name = currName;
  catArray->arr[catArray->n].n_words = 1;
  catArray->arr[catArray->n].words = malloc(sizeof(*catArray->arr[catArray->n].words));
  memCheck(catArray->arr[catArray->n].words);
  catArray->arr[catArray->n].words[0] = currWord;
  catArray->n++;
}


