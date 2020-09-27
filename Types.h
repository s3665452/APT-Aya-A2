#include <vector>
#include <memory>
#include <iostream>

#ifndef TYPES
#define TYPES


#define TURNS   5
#define MOSAIC_DIM  5
#define TILEBAG_MAX_SIZE    100
#define BROKEN_MAX_SIZE 7

// Initial order of the tilebag
const char TILEBAG_ORDER[] = "YBUUYRURRBRLRULLLLLBBRYRLBYURUBULYRULYBYBYRLYLUYUYBYBBUURLLBURRLLBLBLULBYRRBUUYYRYYBBRYUUYUBYBLRLRRU";
const char MOSAIC_ORDER[] = "BYRULLBYRUULBYRRULBYYRBLB";
const int BROKEN_DEDUCTION[] = {0, 1, 2, 4, 6, 8, 11, 14};

const char RED = 'R';
const char YELLOW = 'Y';
const char DARK_BLUE = 'B';
const char LIGHT_BLUE = 'L';
const char BLACK = 'U';
const char FIRST_PLAYER = 'F';
const char NO_TILE = '.';


bool isTile(char c);

void exitGame();

bool contains(std::vector<char>* factory, char tile);

typedef std::vector<char> Broken;
typedef char** Store;
typedef std::pair <char, char> Board[MOSAIC_DIM][MOSAIC_DIM];

#endif //TYPES