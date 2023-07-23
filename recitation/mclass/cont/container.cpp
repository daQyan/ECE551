 #include "container.hpp"


int main(void) {
  // T1 to check the template is int
  Container<int> a(4);
  
  //1. Check the insertNew function
  std::cout << "Checking the insertNew Function!" << std::endl;
  int arr[4] = {0,1,2,3};
  a.insertNew(arr[0]);
  a.insertNew(arr[1]);
  a.insertNew(arr[2]);
  a.insertNew(arr[3]);
  std::cout << "a should be 0 1 2 3"<< std::endl;
  std::cout << "a actually is " << a.getValue(0) << " " << 
  a.getValue(1)  << " " << a.getValue(2) << " " << a.getValue(3) << std::endl;
  
  //2. Check the remove function
  std::cout << "Checking the removeExisting Function!" << std::endl;
  std::cout << "Before removal, a's size is "<< a.getSize() << std::endl;
  a.printVector();
  a.removeExisting(0);
  std::cout << "After removal, a's size is " << a.getSize() << std::endl;
  a.printVector();
  
  //3. Check replace function
  std::cout << "Checking the replaceExisting Function!" << std::endl;
  
  std::cout << "Before replacing, a's first element is " << a.getValue(0) << std::endl;
  a.printVector();
  int num1 = 666;
  a.replaceExisting(0, num1);
  // std::cout << "After replacing, a's first element is " << a.getValue(0) << std::endl;
  a.printVector();

  //4. Suppose the first element is accesssed the least, check insertNew when out of bound
  int num2 = 777;
  int num3 = 999;
  a.insertNew(num2);
  
  std::cout << "a's first element now is replaced by " << a.getValue(0) << std::endl;
  a.printVector();
  a.insertNew(num3);
  a.printVector();


// T2 to check the template is string
  // check corner cases that should exit with failure status
  // remove index out of bounds
  Container<std::string> b(5);
  std::vector<std::string> str_arr = {"I", "am", "a", "man"};
  b.insertNew(str_arr[0]);
  b.insertNew(str_arr[1]);
  b.insertNew(str_arr[2]);
  b.insertNew(str_arr[3]);
  b.removeExisting(4); // out of bounds

}