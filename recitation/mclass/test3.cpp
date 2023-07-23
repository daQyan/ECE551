#include "MyClass.hpp"


// T6 to check the template is string
  // check corner cases that should exit with failure status
  // replace index out of bounds
int main(void) {

  MyClass<std::string> b(5);
  std::vector<std::string> str_arr = {"I", "am", "a", "man"};
  b.insertNew(str_arr[0]);
  b.insertNew(str_arr[1]);
  b.insertNew(str_arr[2]);
  b.insertNew(str_arr[3]);
  b.replaceExisting(4, str_arr[0]); // out of bounds
  return EXIT_SUCCESS;
  
}