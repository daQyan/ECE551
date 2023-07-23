#ifndef TEST_CONTENT_HPP
#define TEST_CONTENT_HPP
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include "category.hpp"
#include "wordDict.hpp"
#include "usedWord.hpp"
#include "utils.hpp"

class content{
private:
    std::vector<std::string> lines;
    usedWord used;

    std::string replaceHelper(std::string str, const std::regex& reg, wordDict dict){
        std::string::const_iterator iterStart = str.begin();
        std::string::const_iterator iterEnd = str.end();
        std::string wordToken;
        std::smatch result;
        if(!regex_search(iterStart, iterEnd, result, reg)){
            return str;
        }
        else{
            wordToken = result[0];
            std::string inside = getInside(wordToken);
            std::regex tokenPattern(wordToken);
            std::string genWord;
            if(dict.checkIfContains(inside)){
                genWord = dict.getCat(inside).chooseWord();
            }else{
                if(!checkIsNum(inside)){
                    ErrHandle("This kind of word does not exist.");
                }
                int reverseIdx = stoi(inside);
                genWord = used.getByReverseIdx(reverseIdx);
            }
            used.addWord(genWord);
            std::string tmp = regex_replace(str, tokenPattern, genWord, std::regex_constants::format_first_only);
            return replaceHelper(tmp, reg, dict);
        }
    }

    static std::string getInside(std::string src){
        //remove the first underline
        src.erase(0, 1);
        return src;
    }
public:
    content(std::string fn) : used() {
        std::ifstream contentFile(fn);
        if(!contentFile){
            ErrHandle("The story file is invalid");
        }
        std::string cur;
        while (getline(contentFile, cur)){
            lines.push_back(cur);
        }
        contentFile.close();
    }
    void printText(){
        for(size_t i=0; i < lines.size(); i++){
            std::cout << lines[i] << std::endl;
        }
    }
    void replaceText(wordDict dict){
        std::regex pattern("_([^(\\s|$|,|.)]*)");
        for(size_t i=0; i < lines.size(); i++){
            lines[i] = replaceHelper(lines[i], pattern, dict);
        }
    }
};
#endif
