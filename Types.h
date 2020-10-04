#include <vector>
#include <memory>
#include <iostream>

#ifndef TYPES
#define TYPES


#define MAX_ROUNDS   5
#define MOSAIC_DIM  5
#define TILEBAG_SIZE    100
#define BROKEN_MAX_SIZE 7

// Initial order of the tilebag
const char TILEBAG_ORDER[] = "YBUUYRURRBRLRULLLLLBBRYRLBYURUBULYRULYBYBYRLYLUYUYBYBBUURLLBURRLLBLBLULBYRRBUUYYRYYBBRYUUYUBYBLRLRRU";
// Order of mosaic
const char MOSAIC_ORDER[] = "BYRULLBYRUULBYRRULBYYRULB";
// Number of points to deduct from broken tiles
const int BROKEN_DEDUCTION[] = {0, 1, 2, 4, 6, 8, 11, 14};

// Colour of the tiles
const char RED = 'R';
const char YELLOW = 'Y';
const char DARK_BLUE = 'B';
const char LIGHT_BLUE = 'L';
const char BLACK = 'U';
const char FIRST_PLAYER = 'F';
const char NO_TILE = '.';

// Check if the character is a tile
bool isTile(char c);

// Say goodbye and exit
void exitGame();

// Check if the factory contains a tile color
bool contains(std::vector<char>* factory, char tile);

// Define broken as an vector<char>
typedef std::vector<char> Broken;

// Define store as a double array
typedef char** Store;

// A 2D array to represent the mosaic
typedef std::pair <char, char> Board[MOSAIC_DIM][MOSAIC_DIM];

#endif //TYPES