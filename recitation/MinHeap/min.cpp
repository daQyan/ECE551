#include "minHeap.hpp"

int main() {
  minHeap<int> mheap(999);
  mheap.insert(1);
  mheap.insert(2);
  mheap.insert(3);
  mheap.insert(4);
  mheap.insert(5);
  mheap.insert(6);
	mheap.removeMin();
}