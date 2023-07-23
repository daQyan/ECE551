#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "provided.h"

//any functions you want your main to use
FILE * safeOpen(char * filename, char * mode, catarray_t * cat);
void safeClose(FILE * f);
char * readTxt(FILE * f);
char * parseTxt(char * txt, catarray_t * catArray, size_t mode, FILE * f);
void printErr(char * str);
catarray_t * readCat(FILE * f);
void freeCat(catarray_t * cat);
void initArr(catarray_t * catArray, char * currName, char * currWord);
int addArr(catarray_t * catArray, char * currName, char * currWord);
void addNewArr(catarray_t * catArray, char * currName, char * currWord);
char * getBlank(char * cur, size_t len);
category_t * initUsedArr();
char * getPrevious(size_t n, category_t * used);
const char * getSubt(char * blk, catarray_t * cat, category_t * used, char * txt, char * txtNew, FILE * f);
void addUsed(const char * subt, category_t * arr);
size_t checkDigit(char * name);
void freeUsed(category_t * used);
void resizeCat(catarray_t * catArray, const char * replace, char * blank, char * txt, char * txtNew, FILE * f, category_t * used);
void checkWordsLeft(char * blk, catarray_t * cat, category_t * used, char * txt, char * txtNew, FILE * f);
void freeHelper(char * blank, catarray_t * cat, category_t * used, char * txt, char * txtNew, FILE * f);
#endif
