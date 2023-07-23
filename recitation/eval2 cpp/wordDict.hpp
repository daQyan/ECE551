#ifndef TEST_WORDDICT_HPP
#define TEST_WORDDICT_HPP

#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <map>
#include "category.hpp"
#include "utils.hpp"
class wordDict{
private:
    std::map<std::string, category> dic;

    void parseLine(std::string line){
        size_t splitter = line.find(':');
        if(splitter == std::string::npos){
            ErrHandle("The word line does not contains splitter! ");
        }
        std::string name = line.substr(0, splitter);
        int existNewline = line.find('\n') == std::string::npos ? 0:1;
        std::string word = line.substr(splitter+1, line.size()-splitter-existNewline);
        std::map<std::string, category>::iterator it = dic.find(name);
        if(it == dic.end()){
            category newWordCat = category(name);
            newWordCat.addWord(word);
            dic.insert(std::pair<std::string, category>(name, newWordCat));
        }else{
            it->second.addWord(word);
        }
    }
public:
    wordDict(std::string fn){
        std::ifstream wordFile(fn);
        if(!wordFile){
            ErrHandle("The word file is invalid");
        }
        std::string cur;
        while (getline(wordFile, cur)){
            parseLine(cur);
        }
        wordFile.close();
    }
    category &getCat(const std::string& catName){
        if(!this->checkIfContains(catName)){
            ErrHandle("There is no such category");
        }
        return dic.find(catName)->second;
    }

    bool checkIfContains(const std::string& name){
        std::map<std::string, category>::iterator it = dic.find(name);
        if(it == dic.end()){
            return false;
        }
        return true;
    }
};
#endif
