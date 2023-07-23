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
    /*
     * construct category and initialize random seed
     */
    category(std::string name):catName(name){
        srand((unsigned int)time(NULL));
    }
    /*
     * add a word to the category
     */
    void addWord(std::string word){
        words.push_back(word);
    }
    /*
     * get the category name
     */
    std::string getCatName(){
        return catName;
    }
    /*
     * print all words in the category
     */
    void printWords(){
        std::cout<< getCatName() <<std::endl;
        for(size_t i = 0;i<words.size();i++){
            std::cout<<"  "<<words[i]<<std::endl;
        }
    }
    /*
     * randomly choose a word from category
     */
    std::string chooseWord(){
        size_t idx = rand()%words.size();
        return words[idx];
    }
};
#endif //TEST_CATEGORY_HPP
