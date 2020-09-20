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

void Factory::setIsFactory(bool isFactory) {
    this->isFactory = isFactory; 
}
bool Factory::getIsFactory () {
    return this->isFactory; 
}
std::string Factory::printTiles(){
    std::cout << factoryTiles << std::endl;
}

