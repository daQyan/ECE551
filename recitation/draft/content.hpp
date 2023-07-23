#ifndef TEST_CONTENT_HPP
#define TEST_CONTENT_HPP
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>
#include "category.hpp"
#include "wordDict.hpp"
#include "usedWord.hpp"
#include "utils.hpp"

class content{
private:
    std::vector<std::string> lines;
    usedWord used;
    /*
     * read content until next \n or space, return content and update
     * index to the end of the content in place
     */
    std::string readInside(std::string & str, size_t & index) {
        std::stringstream buf;
        index++;
        while (index < str.size() 
                && str[index] != '_'
                && str[index] != ' '
                && str[index] != '\n'
                && str[index] != '.'
                && str[index] != ','
                && str[index] != '\t'){

            buf << str[index];
            index++;
        }
        index++;
        return buf.str();
    }

    std::string replaceHelper(std::string str, wordDict dict){
            std::stringstream res;
            std::string wordToken;
            size_t i = 0;
            while (i < str.size()) {
                // if str[i] is not replace indicator push it to result
                if (str[i] != '_') {
                    res << str[i];
                    i++;
                    continue;
                // else get the category name.
                } else {
                    wordToken = readInside(str, i);
                }
                std::string genWord;
                // remove underline
                std::string inside = wordToken;
                // if it is a valid cat, choose a word
                if (dict.checkIfContains(inside)) {
                    genWord = dict.getCat(inside).chooseWord();
                // else check if it is a number and extract data from used
                } else {
                    if (!checkIsNum(inside)) {
                        ErrHandle("This kind of word does not exist.");
                    }
                    int reverseIdx = stoi(inside);
                    genWord = used.getByReverseIdx(reverseIdx);
                }
                used.addWord(genWord);
                res << genWord;
            }
            return res.str();
    }
    //remove the first underline
    static std::string getInside(std::string src){

        src.erase(0, 1);
        return src;
    }
public:
    // construct content that contains lines in provided file
    content(std::string fn) : used() {
        std::ifstream contentFile(fn);
        if(!contentFile){
            ErrHandle("The story file is invalid");
        }
        std::string cur;
        // save lines in the file to lines
        while (getline(contentFile, cur)){
            lines.push_back(cur);
        }
        contentFile.close();
    }
    /*
     * print the content out
     */
    void printText(){
        for(size_t i=0; i < lines.size(); i++){
            std::cout << lines[i] << std::endl;
        }
    }
    /*
     * replace words in content by provided word dictionary
     */
    void replaceText(wordDict dict){
        for(size_t i=0; i < lines.size(); i++){
            lines[i] = replaceHelper(lines[i], dict);
        }
    }
};
#endif
