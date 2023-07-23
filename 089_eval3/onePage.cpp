#include "onePage.hpp"

// check if the string num is a number
void onePage::checkIsNum(size_t pNum, char& ptr) {
    if (pNum == 0 || ptr != '\0') {
        throw std::runtime_error("the element is not a number!");
    }   
}    

// check if the string number is negative
void onePage::checkNeg(std::string& str) {
    if (str[0] == '-') {
        throw std::runtime_error("no negative number!");
    }    
}

// check if there is a hash in the line
void onePage::checkHash(std::string line) {
    if (line[0] != '#') {
        throw std::runtime_error("invalid format, check the '#'! ");
    }
    
}

// parse one line of the txt file and check its format's validity
void onePage::parseOneLine(std::string line, size_t& noHash) {
    size_t splitter = line.find(':');
    if(splitter == std::string::npos){                
        throw std::runtime_error("invalid input, no collon");
    }
    std::string strNum = line.substr(0, splitter);
    checkNeg(strNum);
    char * ptr;
    size_t pNum = strtol(strNum.c_str(), &ptr, 10);
    // std::cout << std::endl << pNum << std::endl;
    checkIsNum(pNum, *ptr);
    // int ifNewline = line.find('\n') == std::string::npos ? 0:1;          
    std::string word = line.substr(splitter+1, line.size() - splitter - 1);
    // add to the navigation list
    navigTxt.push_back(std::pair<size_t, std::string>(pNum, word));        
}


/// @brief parse each line of the txt file and check its format's validity
/// @param noHash is the identifier to see if the file contains the hash symbol
void onePage::getNavigLine(std::string line, std::ifstream& f, size_t& noHash) {     // reference use?    
    while (getline(f, line)) {
        // get the navigation info until reach '#'
        size_t splitter = line.find(':');
        if(splitter == std::string::npos){
            if (line[0] == '#') {
                noHash = 0;
                break;
            }
            throw std::runtime_error("invalid input, no collon");
        }
        std::string strNum = line.substr(0, splitter);
        char * ptr;
        checkNeg(strNum);
        size_t pNum = strtol(strNum.c_str(), &ptr, 10);
        checkIsNum(pNum, *ptr);
        std::string word = line.substr(splitter+1, line.size() - splitter - 1);
        // add to the navigation list
        navigTxt.push_back(std::pair<size_t, std::string>(pNum, word));        
    }        
}


// print the content of one page
void onePage::printPage() {
    // print if win
    if (navigMode == LOSE) {
        for(size_t i=0; i < text.size(); i++){
            std::cout << text[i] << std::endl;
        }
        std::cout << std::endl << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    // print if lose
    if (navigMode == WIN) {
        for(size_t i=0; i < text.size(); i++){
            std::cout << text[i] << std::endl;
        }
        std::cout << std::endl << "Congratulations! You have won. Hooray!" << std::endl;
    }        
    if (navigMode == STEP) {
        // text print
        for(size_t i=0; i < text.size(); i++){
            std::cout << text[i] << std::endl;
        }
        // print guide
        std::cout << std::endl << "What would you like to do?\n" << std::endl;
        std::vector<std::pair<size_t, std::string> >::iterator i = navigTxt.begin();
        size_t n = 1;
        while (i != navigTxt.end()) {
            std::cout << " " << n << ". " << i->second << std::endl;
            ++n;
            ++i;
        }
    }
}


