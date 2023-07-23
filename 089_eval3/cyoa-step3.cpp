#include "styBook.hpp"

// STEP 3
// get the depth of each page in the story
int main(int argc, char** argv) {
    if(argc!=2){
        perror("Invalid arg numbers!");
        return EXIT_FAILURE;
    }
    try {
        styBook book = styBook(argv[1]);
        std::vector<size_t> depth = book.getDepth();
        book.printDepth(depth);
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


