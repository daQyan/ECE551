#ifndef TEST_UTILS_HPP
#define TEST_UTILS_HPP

#include <string>
#include <iostream>

void ErrHandle(const std::string msg){
    std::cerr<< msg <<std::endl;
    exit(EXIT_FAILURE);
}

bool checkIsNum(std::string str){
    for (size_t i = 0; i < str.size(); i++){
        char tmp = str[i];
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
