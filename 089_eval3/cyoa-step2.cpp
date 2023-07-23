#include "styBook.hpp"

// STEP 2
// check the reference validity of each page and play the game
int main(int argc, char** argv) {
    if(argc!=2){
        perror("Invalid arg numbers!");
        exit(EXIT_FAILURE);
    }
    try {
        styBook book = styBook(argv[1]);
        book.goPlay();
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

