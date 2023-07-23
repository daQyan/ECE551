#include <cmath>
#include <cstdio>
#include <cstdlib>

#include "function.h"

//int binarySearchForZero(function, low, high);
int binarySearchForZero(Function<int, int> * f, int low, int high);


class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};


void check(Function<int,int> * f,
    int low,
	  int high,
	  int expected_ans,
	  const char * mesg) {
    int n;
    if (high > low) {
      n = log2(high - low) + 1;
    } 
    else {
      n = 1;
    }
    CountedIntFn * func = new CountedIntFn(n, f, mesg);

    int ans = binarySearchForZero(func, low, high);
    if (ans != expected_ans) {
      fprintf(stderr, "expected invokes: %d, but actually has: %d", expected_ans, ans);
      exit(EXIT_FAILURE);
    }
}


class Function_pos : public Function<int, int> {
  public:
    virtual int invoke(int arg) {
      return arg - 2 ;
    }
};


int main() {
  Function_pos f1;      ///
  check(&f1, -9999, -3333, -3334, "all negative\n");
  check(&f1, 3333, 9999, 3333, "all positive\n");
  // check(&f1, 1, 3333, 2, "inclusive zero\n");
  check(&f1, -9999, 0, -1, "exclusive zero\n");
  check(&f1, 0, 8191, 2, "normal\n");
  return EXIT_SUCCESS;
}

