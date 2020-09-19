#include "Factory.h"
#include "TileBag.h"

Factory::Factory() {

}

Factory::~Factory() {

}

Factory::Factory(const Factory&) {
    //todo
}

void Factory::add(TileBag tileBag) {
    //allTiles->push_back(tileBag->getFirstTile());
}

void Factory::remove(int i) {
    //error>>>>>>>allTiles[i]->clear();
    
}

int Factory::getSize() {
    return allTiles->size();
}