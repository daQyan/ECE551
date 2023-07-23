#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
//using namespace std;
template<typename T>

class Container{
private:
  size_t max_sz;
  // A vector of pairs contains the instantiation and its appear times
  std::vector<std::pair<T, size_t> > vec;

public:
  //Constructor that the parameters define how many elements can be at most contained
  Container(size_t size): max_sz(size){}
  
  //The destructor
  ~Container(){}
  
  //The Copy Constructor
  Container(const Container & rhs) : max_sz(rhs.max_sz), vec(rhs.vec){}
  
  //The Assignment Constructor
  Container & operator=(const Container<T> &rhs){
    if(this == &rhs){
        return *this;
    }
    max_sz = rhs.max_sz;
    vec = rhs.vec;
    return *this;
  }
  
  //check if the position is valid, record one more time it has been
  //accessed, and returns a copy of the contained element
  T getValue(size_t pos){
    if(pos >= vec.size()){
      std::cerr << "The index "  << pos << "is out of bound!" << std::endl;
    }
    vec[pos].second ++;
    return vec[pos].first;
  }
  
  //get the size of the vector
  size_t getSize(){
    return vec.size();
  }

  //times of access at the position
  size_t numOfGetValue(size_t pos){
    return vec[pos].second;
  }
  
  /*
  Adds a new element to the container
  If there is no place to add, if there is no space left, the element with the minimal
  number of accesses will be deleted and the new element will be written in that position
  */
  void insertNew(T & new_element){       
    if(vec.size() < max_sz){
        std::pair<T, size_t> p(new_element, 0);
        vec.push_back(p);
        return;
    }  
    size_t temp = vec[0].second;
    size_t ind;
    //find the postion with the minimal number of accesses
    for(size_t i = 0; i < vec.size(); i++){
     if(temp > vec[i].second){
        ind = i;
        std::cout << "Currently, ind is: " << ind << std::endl;
        temp = vec[i].second;
     }
    }
    replaceExisting(ind, new_element);
  }
  
  /*
    This method takes a parameter positon.
    It removes the existing elements by its index. 
    If the passing index is out of bound, it will exit with error messgae
  */  
  void removeExisting(size_t pos){
    if(pos >= vec.size()){
      std::cerr << "The index "  << pos << " is out of bound!" << std::endl;
    }
    vec.erase(vec.begin() + pos);
  }
  
  /*
    replaces the element at position size_t with a new one, 
    if the position is out of bound, it will exit with error message
  */
  void replaceExisting(size_t pos, T & new_element){
    if(pos >= vec.size()){
      std::cerr << "The index "  << pos << " is out of bound!" << std::endl;
    }
    vec[pos].first = new_element;
    vec[pos].second = 0;
  }
  
  /*
  This method prints the vector of pairs.
  It is to check the elements in the vector of pairs. 
  Inside this function, no getValue was called!
  */
  void printVector(){
    std::cout << "The vector is: (The element, the access times)" << std::endl;
    std::cout << "The vector is: " << std::endl;
    for(size_t i = 0; i < vec.size()-1; i++){
      std::cout << "(" << vec[i].first << ", " << vec[i].second << ")" << std::endl;
    }
    std::cout << "(" << vec[vec.size()-1].first << ", " << vec[vec.size()-1].second << ")" << std::endl;
  }
};


