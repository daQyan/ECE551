#ifndef __COUNTS_H__
#define __COUNTS_H__
struct _one_count_t {
  //DEFINE ME
  char * strCount;
  size_t numCount;

};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  one_count_t ** countArray;
  size_t numArray;
  size_t numUnknown;
  //DEFINE ME
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
