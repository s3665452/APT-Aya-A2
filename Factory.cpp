#include "Factory.h"
#include "TileBag.h"

Factory::Factory() {

    this->isFactory = false;

}

Factory::~Factory() {

}


void Factory::add(char tile) {
    factoryTiles->push_back(tile);
}

void Factory::remove(){
        factoryTiles->clear();
 
}

int Factory::getSize() {
    return factoryTiles->size();
}

void setIsFactory(bool isFactory) {
    this->isFactory = isFactory; //error
}
bool getIsFactory () {
    return this->isFactory; //error
}

