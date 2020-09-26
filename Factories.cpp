#include "Factories.h"
#include "TileBag.h"
#include "vector"

Factories::Factories(TileBag* tileBag) {
    fillFactories(tileBag);
}

Factories::~Factories() {

}

// Get the pointer of a factory
std::vector<char>* Factories::getFactory(int index) {
    return &(this->factories[index]);
}

// Fill the factories with tiles
void Factories::fillFactories(TileBag* tileBag) {
    // Add F to the centre
    factories[0].push_back('F');
    // Populate factories with tiles from the tile bag
    for(int i = 1; i < FACTORYNUMBER; i++) {
        for(int n = 0; n < FACTORYSIZE; n++){
            factories[i].push_back(tileBag->front());
            tileBag->dequeue();
        }
    }
}

// Return true if all factories are empty
bool Factories::isEmpty() {
    bool ret = true;
    int i = 0;
    while(i < FACTORYNUMBER &&  !factories[i].size()) {
        i += 1;
    }
    if(i < FACTORYNUMBER) {
        ret = false;
    }
    return ret;
}



