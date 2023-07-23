#ifndef TEST_CATEGORY_HPP
#define TEST_CATEGORY_HPP

#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
class category{
private:
    std::string catName;
    std::vector<std::string> words;
public:
    category(std::string name):catName(name){}
    void addWord(std::string word){
        words.push_back(word);
    }

    std::string getCatName(){
        return catName;
    }

    void printWords(){
        std::cout<< getCatName() <<std::endl;
        for(size_t i = 0;i<words.size();i++){
            std::cout<<"  "<<words[i]<<std::endl;
        }
    }

    std::string chooseWord(){
        srand((unsigned int)time(NULL));
        size_t idx = rand()%words.size();
        return words[idx];
    }
};
#endif //TEST_CATEGORY_HPP
