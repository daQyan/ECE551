#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
template<typename T>

class MyClass{
private:
  size_t max_sz;
  // A vector of pairs contains the instantiation and its appear times
  std::vector<std::pair<T, size_t> > vec;

public:
  //Constructor that the parameters define how many elements can be at most contained
  MyClass(size_t size): max_sz(size){}
  
  //The destructor
  ~MyClass(){}
  
  //The Copy Constructor
  MyClass(const MyClass & rhs) : max_sz(rhs.max_sz), vec(rhs.vec){}
  
  //The Assignment Constructor
  MyClass & operator=(const MyClass<T> &rhs){
    if(this == &rhs){
        return *this;
    }
    max_sz = rhs.max_sz;
    vec = rhs.vec;
    return *this;
  }
  
  
  //Checks if the position is valid and returns a copy of the contained element
  T getValue(size_t pos){
    if(pos >= vec.size()){
      std::cerr << "The index "  << pos << "is out of bound!" << endl;
    }
    vec[pos].second ++;
    return vec[pos].first;
  }
  
  //get the size of the vector
  size_t getSize(){
    return vec.size();
  }

  size_t numOfGetValue(size_t pos){
    return vec[pos].second;
  }
  
  //Adds a new element to the container
  void insertNew(T & new_element){       
    if(vec.size() < max_sz){
        std::pair<T, size_t> p(new_element, 0);
        vec.push_back(p);
        return;
    }  
    size_t temp = vec[0].second;
    size_t ind;
    for(size_t i = 0; i < vec.size(); i++){
     if(temp > vec[i].second){
        ind = i;
        cout << "Currently, ind is: " << ind << endl;
        temp = vec[i].second;
     }
    }
    replaceExisting(ind, new_element);
  }
  
  /*
    This method takes a parameter positon.
    It removes the existing elements by its index. 
    If the passing index is out of bound, it exit with error messgae
  */  
  void removeExisting(size_t pos){
    if(pos >= vec.size() || pos < 0){
      std::cerr << "The index "  << pos << " is out of bound!" << endl;
    }
    vec.erase(vec.begin() + pos);
  }
  
  void replaceExisting(size_t pos, T & new_element){
    if(pos >= vec.size() || pos < 0){
       std::cerr << "The index "  << pos << " is out of bound!" << endl;
       exit(EXIT_FAILURE);
     }
    vec[pos].first = new_element;
    vec[pos].second = 0;
  }
  
  /*
  This method prints the vector of pairs
  */
  void printVector(){
    cout << "The vector is: (The element, the access times)" << endl;
    // cout << "The vector is: " << endl;
    for(size_t i = 0; i < vec.size()-1; i++){
      cout << "(" << vec[i].first << ", " << vec[i].second << ")" << endl;
    }
    cout << "(" << vec[vec.size()-1].first << ", " << vec[vec.size()-1].second << ")" << endl;
  }
};


