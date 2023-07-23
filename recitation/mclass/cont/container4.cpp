#include "container.hpp"


// check the functionality when T is string type
int main(void) {

  Container<std::string> b(5);
  std::vector<std::string> str_arr = {"I", "am", "a", "man"};

  std::cout << "Checking the insertNew Function!" << std::endl;
  b.insertNew(str_arr[0]);
  b.insertNew(str_arr[1]);
  b.insertNew(str_arr[2]);
  b.insertNew(str_arr[3]);
  std::cout << "b should be I am a man"<< std::endl;
  std::cout << "b actually is " << b.getValue(0) << " " << 
  b.getValue(1)  << " " << b.getValue(2) << " " << b.getValue(3) << std::endl;
  
  //2. Check the remove function
  std::cout << "Checking the removeExisting Function!" << std::endl;
  std::cout << "Before removal, a's size is "<< b.getSize() << std::endl;
  b.printVector();
  b.removeExisting(0);
  std::cout << "After removal, a's size is " << b.getSize() << std::endl;
  b.printVector();
  
  //3. Check replace function
  std::cout << "Checking the replaceExisting Function!" << std::endl;
  
  std::cout << "Before replacing,  " << b.getValue(0) << std::endl;
  b.printVector();
  std::string str1 = "My roommate";
  b.replaceExisting(0, str1);
  std::cout << "After replacing, the vector becomes " << std::endl;
  b.printVector();

  //4. Now the first element is accesssed the least, check insertNew when out of bound
  std::cout << "Checking the inserting when out of bound!" << std::endl;
  std::string str2 = "My roommate";
  std::string str3 = "His roommate";
  b.insertNew(str2);
  b.getValue(0);
  std::cout << "before inserting an extra string " << b.getValue(0) << std::endl;
  b.printVector();
  b.insertNew(str3);
  std::cout << "after inserting an extra string, the last one shoulde be replaced " << std::endl;
  b.printVector();

  return EXIT_SUCCESS;
  
}