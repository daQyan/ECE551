#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  while (low + 1 < high) {
    int mid = (low + high) / 2;
    int idx = f->invoke(mid);
    if (idx == 0) {
      return mid;
    }
    else if (idx > 0) {
      high = mid;
    }
    else {
      low = mid;
    }
  }
  return low;  
}
