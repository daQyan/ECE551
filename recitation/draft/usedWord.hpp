#ifndef TEST_USEDWORD_HPP
#define TEST_USEDWORD_HPP
#include "utils.hpp"
class usedWord{
private:
    std::vector<std::string> words;
public:
    /*
     * add a word to usedWord
     */
    void addWord(std::string word){
        words.push_back(word);
    }
    /*
     * get the index-th words from back
     */
    std::string getByReverseIdx(size_t idx){
        if(idx>words.size()){
            ErrHandle("The number token is out of range");
        }
        return words[words.size()-idx];
    }
};
#endif
