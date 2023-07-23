#include <vector>
#include "wordDict.hpp"
#include "content.hpp"
int main(int argc, char** argv){
    srand((unsigned int)time(NULL));
    if(argc!=3){
        ErrHandle("Invalid arg numbers!");
    }
    wordDict wrdInstance = wordDict(argv[1]);
    content ctnInstance = content(argv[2]);
    ctnInstance.replaceText(wrdInstance);
    ctnInstance.printText();
    return EXIT_SUCCESS;
}
