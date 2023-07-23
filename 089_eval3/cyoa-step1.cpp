#include "onePage.hpp"

// STEP 1
// read and store one page and print its content
int main(int argc, char** argv) {
    if(argc!=2){
        perror("Invalid arg numbers!");
        return EXIT_FAILURE;
    }
    try {
        onePage page = onePage(argv[1]);
        page.printPage();
    }    
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


