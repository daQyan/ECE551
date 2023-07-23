#include "MyData.hpp"


int main(){
    MyDataS<int> mydata;
    mydata.insert(100);
    mydata.insert(50);
    mydata.insert(30);
    mydata.insert(200);
    mydata.insert(300);
    mydata.insert(250);
    mydata.insert(40);
    mydata.insert(1);
    mydata.insert(999);
    std::cout << "The Insertion of the Minmydata: " << std::endl;
    mydata.sort(); 

    std::cout << "The first remove of Minmydata" << std::endl;
    mydata.remove(1);
    mydata.sort();
    std::cout << "The min of is: " << mydata.getmin() << std::endl;
    
    std::cout << "The next remove of MinHeap " << std::endl;
    mydata.remove(30);
    mydata.sort();

    std::cout << "The min of is: " << mydata.getmin() << std::endl;
    return EXIT_SUCCESS;

}