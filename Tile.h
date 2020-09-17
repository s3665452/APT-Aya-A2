#ifndef TILE
#define TILE

#include "ColorTile.h"

class Tile {
public:

    // Constructor/Deconstructor
    Tile(Colour colour_);
    ~Tile();

    // get the colour of the tiles
    Colour getColour();

    // Set the colour
    void setColour(Colour colour_);

    // check if it is the same color
    bool isSimilarColour(Tile* tiles);

private:
   Colour colour;
};

#endif //TILE