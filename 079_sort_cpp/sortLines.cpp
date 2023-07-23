#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>


void sortLine(std::istream & in) {
  std::string line;
  std::vector<std::string> lines;
  while (std::getline(in, line)) {
    lines.push_back(line);
  }
  if ((!in) && (!in.eof())) {                                             // checkkkkkkkkkk!!!!
    std::cerr << "Error occurred when reading file\n";
    exit(EXIT_FAILURE);
  }
  std::sort(lines.begin(), lines.end());
  std::vector<std::string>::iterator i = lines.begin();
  while (i != lines.end()) {
    std::cout << *i << std::endl;
    ++i;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sortLine(std::cin);
  } else if (argc > 1) 
  {
    for (int i = 1; i < argc; i++) {
    std::ifstream input(argv[i]);
    if (!input.is_open()) {
        std::cerr << "Error opening file: " << argv[i] << std::endl;
        exit(EXIT_FAILURE);                                                         // check!!!!!!!!!!!!!!!!!
    }
    sortLine(input); 
    input.close();                
  } 
  }
  return EXIT_SUCCESS;
}
