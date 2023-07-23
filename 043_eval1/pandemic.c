#include "pandemic.h"
#include <stdio.h>
#include <string.h>   
#include <ctype.h>

// abstract the error checking function
void printErr(char * str) {
  fprintf(stderr, "Error: %s!\n", str);
  exit(EXIT_FAILURE);
}
// abstract the null checker
void checkNull(void * target, char * str) {
  if (target == NULL) {  
    printErr(str);
  }
}

// Step 1
country_t parseLine(char * line) {
  country_t ans;
  ans.name[0] = '\0';
  ans.population = 0;
  // check if the line is NULL
  checkNull(line, "invalid input, check the line");
  // assign two pointers, one at the line, another at the comma
  char *ptr = line;
  char *ptrComma = strchr(line, ',');
  // check if the string has a comma
  checkNull(ptrComma, "invalid input, check the comma");
  // check if the whole population part has data and is a number
  ptrComma++;                               // now point at the first character after comma
  if (*ptrComma == '\0' || isalpha(*ptrComma) || *ptrComma == '\n') {
    printErr("no population data");
  }
  // start reading the country name
  int i = 0;
  while (*ptr != ',') {                     
    ans.name[i] = *ptr;
    ptr++;
    i++;  
    // check name length, and leave an extra space for '\0'
    if (i > MAX_NAME_LEN-1) {   
      printErr("Country name is too long");
    }
  }  
  ans.name[i] = '\0';            
  // read the population 
  ans.population = atoi(ptrComma);
  return ans;
}

//Step 2
void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  // check if the data/avg is NULL and if there are at least 7 days for average
  checkNull(data, "data is null");
  checkNull(avg, "avg is null");
  if (n_days < 7) {
    printErr("too few days (< 7days)");             
  }

  double cum7 = 0.0;
  double *calRunningAvg = avg;
  unsigned *ptrDataTemp = data;
  // go through each number in data except the last 6 ones
  // meanwhile calculate each 7 day sum for each advance of the pointer of data  
  for (size_t i = 0; i < n_days-6; i++) {     
    for (size_t j = 0; j < 7; j++) {          
      cum7 += *ptrDataTemp;
      ptrDataTemp++;
    }
    *calRunningAvg = cum7/7.0;                      // then get the average value accordingly
    calRunningAvg++;                           
    cum7 = 0.0;                                     // reset the sum of 7-day data
    data++;                                         // forward to the next data
    ptrDataTemp = data;                             // reset the pointer to the next data 
  }
}

// Step 3
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  // check if the data/cum is NULL or no days input
  checkNull(data, "data is null");
  checkNull(cum, "cum is null");
  if (n_days == 0) {
    printErr("no n_days input");             
  }
  // loop throug tha data and add case numbers to sum
  double sum = 0.0;
  double *calSum = cum;
  for (size_t i = 0; i < n_days; i++) {
    sum += *data;
    *calSum = (sum/pop) * 100000.0;
    calSum++;
    data++;
  }  
}

// Step 4
void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  // check if the data/countries is NULL or no days/countries input
  checkNull(data, "data is null");
  checkNull(countries, "countries is null");
  if (n_countries == 0 || n_days == 0) {
    printErr("no input of days or countries");
  }
  // loop through each countries' case at each day
  // find the max case, and the according country index to save
  unsigned maxCase = 0;
  size_t maxCountryIndex;
  for (size_t i = 0; i < n_countries; i++) {
    for (size_t j = 0; j < n_days; j++) {
        if (data[i][j] > maxCase) {
          maxCase = data[i][j];
          maxCountryIndex = i;
        }
    }
  }
  // the lastly scanned country with max cases will be printed if there is a tie
  printf("%s has the most daily cases with %u\n", countries[maxCountryIndex].name, maxCase);
}
