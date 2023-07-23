#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

// assign the type of each page
enum navigType { WIN, LOSE, STEP };

/** OnePage is one page of the story 
     * @param text is the text at the end
     * @param navigTxt is the choices page number and its according text
     * @param navigMode is the mode of this page, WIN, LOSE, STEP, and STEP means this page has page choices to jump
     * @param pageIndex is the page number of this page
     */
class onePage{
private:
    std::vector<std::string> text;
    std::vector<std::pair<size_t, std::string> > navigTxt;
    navigType navigMode;       // LOSE WIN STEP
    size_t pageIndex;
    
    void checkHash(std::string line);      
    void parseOneLine(std::string line, size_t& noHash);
    void getNavigLine(std::string line, std::ifstream& f, size_t& noHash);
    void checkIsNum(size_t pNum, char& ptr);
    void checkNeg(std::string& str);
    
public:

    // print the content of the page
    void printPage();
    // constructor 
    onePage() {}  

    /** construct the page 
     * @param fname is the file name
     */
    onePage(std::string fname) {
        std::ifstream f(fname);
        if (!f) {
            throw std::runtime_error("open file fail!");
        }
        std::string line;
        getline(f, line); 

        if (line.compare("WIN") == 0) {
            navigMode = WIN;
            getline(f, line);
            checkHash(line);
        }
        else if (line.compare("LOSE") == 0) {
            getline(f, line);
            navigMode = LOSE;
            checkHash(line);
        }
        else {
            navigMode = STEP;
            size_t noHash = 1;
            parseOneLine(line, noHash);
            getNavigLine(line, f, noHash);  
            
            if (noHash) {
                throw std::runtime_error("no hash in the file!");
            }
        }        
        // read the reamaining text part                
        while (getline(f, line)) {            
            text.push_back(line);
        }        
        f.close();
    }
    // allow styBook to access the private part of onePage
    friend class styBook;
};