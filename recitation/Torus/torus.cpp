/*
* Recitation 11
* Zeyu Yuan(zy161), Jing Wang(jw844), Haoyan Li(hl467)
*/


#include <vector>
#include <string>
#include <iostream>


template <typename T>
class torus {
private:
    std::vector<T> myTorus;
    typename std::vector<T> :: const_iterator c_it;
public:
    torus(){};
    void Add(const T & item);
    void Remove(const T & item);
    void Print();
    void Circle_Print(int times);
    torus & operator++(){
        if(*c_it == myTorus.end() - 1){
            c_it = myTorus.begiin();
        }
        else{
            c_it += 1;
        }
    };
};

template <typename T>
void torus<T>:: Add (const T & item){
    myTorus.push_back(item);
}

template <typename T>
void torus<T>:: Remove (const T & item){
    int exist = 0;
    typename std::vector<T> :: iterator it = myTorus.begin();
    while(it != myTorus.end()){
        if(*it == item){
            exist = 1;
            myTorus.erase(it);
        }
        it++;
    }
    if(exist == 0){
        std::cerr << "There's no according element in the torus!" << std::endl;
    }
}

template <typename T>
void torus<T>:: Circle_Print (int times){
    torus<T> c_it();
    int i = 0;
    while(i < times){
        std::cout << *c_it << std::endl;
        c_it++;
        i++;
    }
}

int main()
{
    torus<int> test1;
    // test the type int
    std::cout << "Test1 begins:" << std::endl;
    // test1.Print();
    test1.Add(1);
    test1.Add(2);
    test1.Add(3);
    test1.Add(4);
    test1.Add(5);
    // test1.Print();
    test1.Remove(3);
    // test1.Print();
    std::cout << "*********" << std::endl;

    // test the type string
    torus<std::string> test2;
    std::cout << "Test2 begins:" << std::endl;
    test2.Add("Yang_Ouyang");
    test2.Add("ZiLin_Xu");
    test2.Add("Jennifer");
    test2.Circle_Print(5);
    // test2.Remove("ZiLin_Xu");
    // test2.Circle_Print(3);
}
