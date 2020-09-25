#include <vector>
#include <memory>
#include <iostream>

#ifndef TYPES
#define TYPES


#define TURNS   5
#define MOSAIC_DIM  5
#define FACTORY_SIZE 4
#define TILEBAG_MAX_SIZE    100

// Initial order of the tilebag
const char TILEBAG_ORDER[] = "YBUUYRURRBRLRULLLLLBBRYRLBYURUBULYRULYBYBYRLYLUYUYBYBBUURLLBURRLLBLBLULBYRRBUUYYRYYBBRYUUYUBYBLRLRRU";

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
typedef char Board[MOSAIC_DIM][MOSAIC_DIM];

#endif //TYPES