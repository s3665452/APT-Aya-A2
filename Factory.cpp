#include "Factory.h"
#include "Tile.h"

Factory::Factory() {

}

Factory::~Factory() {

}

Factory::Factory(const Factory&) {
    //todo
}

void Factory::add(Tile argTile) {
    allTiles->push_back(argTile);
}

void Factory::remove(int i) {
    //error>>>>>>>allTiles[i]->clear();
    
}

int Factory::getSize() {
    return allTiles->size();
}