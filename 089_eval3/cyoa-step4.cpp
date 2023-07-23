#include "styBook.hpp"

// STEP 4
// get all the win path
int main(int argc, char** argv) {
	if(argc!=2){
		perror("Invalid arg numbers!");
		return EXIT_FAILURE;
	}
    
	try {
		styBook book = styBook(argv[1]);
  	book.findExit();
	}

	catch(const std::exception& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}


