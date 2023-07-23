#include "container.hpp"

// check when the template is string
// check corner cases that should exit with failure status
// when replace index out of bounds
int main(void) {
  Container<std::string> b(5);
  std::vector<std::string> str_arr = {"I", "am", "a", "man"};
  b.insertNew(str_arr[0]);
  b.insertNew(str_arr[1]);
  b.insertNew(str_arr[2]);
  b.insertNew(str_arr[3]);
  b.printVector();
  std::cout << "Checking the removeExisting Function when index is out of bound!" << std::endl;
  b.replaceExisting(4, str_arr[0]); 
  b.printVector();
  return EXIT_SUCCESS;
  
}