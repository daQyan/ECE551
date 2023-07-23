#include <cstdio>
#include <cstdlib>

#include "bstset.h"


int main() {
  BstSet<int> map;
  map.add(33);
  map.add(44);
  map.add(12);
  map.add(55);
  map.add(99);
  map.add(16);
  map.add(77);
  map.add(0);
  map.add(-1);
  map.add(100);

  std::cout << "The expected answer is -1 0 12 16 33 44 55 77 99 100" << std::endl;
  // // map.inOrderPrint();
  // int ans1 = map.lookup(44);
  // // int ans2 = map.lookup(77);
  // std::cout << "ans1 should be 2 and =" << ans1 << "\n";
  // std::cout << "ans2 should be 7 and =" << ans2 << "\n";
  map.remove(12);
  // map.inOrderPrint();

  // BstMap<int, int> map2(map);
  // map2.inOrderPrint();

  return EXIT_SUCCESS;
}