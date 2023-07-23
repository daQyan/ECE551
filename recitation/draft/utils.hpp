#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>
#include <iostream>
/*
 * print error message and exit
 */
void ErrHandle(const std::string msg){
    std::cerr<< msg <<std::endl;
    exit(EXIT_FAILURE);
}
/*
 * check if a string is a valid number
 */
bool checkIsNum(std::string str){
    if (str.size() == 0) {
        return false;
    }
    for (size_t i = 0; i < str.size(); i++){
        char tmp = str[i];
        // most significand digit should not be zero
        if (i==0){
            if(tmp<'1' || tmp>'9'){
                return false;
            }
        }
        else{
            if(tmp<'0' || tmp>'9'){
                return false;
            }
        }
    }
    return true;
}

#endif //TEST_UTILS_HPP
