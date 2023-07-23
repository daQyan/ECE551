#include "container.hpp"

int main(void) {
  Container<int> a(4);

  //Check the insertNew function
  std::cout << "Checking the insertNew Function!" << std::endl;
  int arr[4] = {0,1,2,3};
  a.insertNew(arr[0]);
  a.insertNew(arr[1]);
  a.insertNew(arr[2]);
  a.insertNew(arr[3]);

  //check the printVector function
  std::cout << "Checking the printVector Function!" << std::endl;
  a.printVector();

  //check the getValue function
  std::cout << "Checking the getValue Function!" << std::endl;
  std::cout << "a should be 0 1 2 3"<< std::endl;
  std::cout << "a actually is " << a.getValue(0) << " " << 
  a.getValue(1)  << " " << a.getValue(2) << " " << a.getValue(3) << std::endl;
  
  //Check the remove function
  std::cout << "Checking the removeExisting Function!" << std::endl;
  std::cout << "Before removal, a's size is "<< a.getSize() << std::endl;
  a.printVector();
  a.removeExisting(0);
  std::cout << "After removal, a's size is " << a.getSize() << std::endl;
  a.printVector();
  
  //Check replace function
  std::cout << "Checking the replaceExisting Function!" << std::endl;
  std::cout << "Before replacing, a's first element is " << a.getValue(0) << std::endl;
  a.printVector();
  int num1 = 666;
  a.replaceExisting(0, num1);
  a.printVector();
  std::cout << "a's first element now is replaced by " << a.getValue(0) << std::endl;

  //check the insertNew function when size is maxmized
  //Now the first element is accesssed the least, check insertNew when out of bound
  int num2 = 777;
  int num3 = 999;
  a.insertNew(num2);
  
  a.printVector();
  a.insertNew(num3);
  a.printVector();
  std::cout << "777 is replaced by 999" << a.getValue(0) << std::endl;

  return EXIT_SUCCESS;

}