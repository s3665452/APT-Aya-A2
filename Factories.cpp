#include "Factories.h"
#include "TileBag.h"
#include "vector"

Factories::Factories(TileBag& tileBag) {
    fillFactories(tileBag);
}

Factories::~Factories() {

}

// Get a factory
std::vector<char> Factories::getFactory(int index) {
    return this->factories[index];
}

// Fill the factories with tiles
void Factories::fillFactories(TileBag& tileBag) {
    // Add F to the centre
    factories[0].push_back('F');
    // Populate factories with tiles from the tile bag
    for(int i = 1; i < FACTORYNUMBER; i++) {
        for(int n = 0; n < FACTORYSIZE; n++){
            factories[i].push_back(tileBag.getFirstTile());
        }
    }
}



