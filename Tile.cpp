#include "Tile.h"

#include <iostream>

//contructor of the given tile
Tile::Tile(Colour colour_){
    this->colour = colour_;
}

Tile::~Tile(){
    
}

Colour Tile::getColour(){
    return this->colour;
}

void Tile::setColour(Colour colour_){
    this->colour = colour_;
}

//check if the color of the two tiles are the same
bool Tile::isSimilarColour(Tile* tiles){
    if (tiles->getColour() == this->colour){
        return true;
    }
        return false;
}
	








