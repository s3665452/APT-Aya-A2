#include "Types.h"

bool isTile(char c) {
    bool ret = false;
    if(c == 'R' || c == 'Y' || c == 'B' || c == 'L' || c == 'U' || c == 'F') {
        ret = true;
    }
    return ret;
}


void exitGame(){
    std::cout << std::endl << "Goodbye" << std::endl;
    exit(EXIT_SUCCESS);
}


bool contains(std::vector<char>* factory, char tile) {
    bool ret = false;
    for(char& c : *factory) {
        if(c == tile) {
            ret = true;
        }
    }
    return ret;
}