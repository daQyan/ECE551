#include "MyClass.hpp"

// T1
int main(void) {
  MyClass<int> a(4);
  
  //1. Check the insertNew function
  std::cout << "Checking the insertNew Function!" << endl;
  int arr[4] = {0,1,2,3};
  a.insertNew(arr[0]);
  a.insertNew(arr[1]);
  a.insertNew(arr[2]);
  a.insertNew(arr[3]);
  std::cout << "a should be 0 1 2 3"<< std::endl;
  std::cout << "a actually is " << a.getValue(0) << " " << 
  a.getValue(1)  << " " << a.getValue(2) << " " << a.getValue(3) << std::endl;
  
  //2. Check the remove function
  std::cout << "Checking the removeExisting Function!" << endl;
  std::cout << "Before removal, a's size is "<< a.getSize() << std::endl;
  a.printVector();
  a.removeExisting(0);
  std::cout << "After removal, a's size is " << a.getSize() << std::endl;
  a.printVector();
  
  //3. Check replace function
  std::cout << "Checking the replaceExisting Function!" << endl;
  
  std::cout << "Before replacing,  " << std::endl;
  a.printVector();
  int num1 = 666;
  a.replaceExisting(0, num1);
  std::cout << "After replacing, the vector becomes " << std::endl;
  a.printVector();

  //4. Now the first element is accesssed the least, check insertNew when out of bound
  std::cout << "Checking the inserting when out of bound!" << endl;
  int num2 = 777;
  int num3 = 999;
  a.insertNew(num2);
  a.getValue(0);
  std::cout << "before inserting an extra number  " << std::endl;
  a.printVector();
  a.insertNew(num3);
  std::cout << "after inserting an extra number, the last one shoulde be replaced " << std::endl;
  a.printVector();

  return EXIT_SUCCESS;

}