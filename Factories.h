#include <vector>
#include <array>
#include "TileBag.h"

// The size of a factory
#define FACTORYSIZE 4
// Total number of factories
#define FACTORYNUMBER 6

class Factories {
    public:
        // Constructor of factories, gets tiles from the tile bag to populate factories
        Factories(TileBag* tileBag);

        // Deconstructor
        ~Factories();

        // Fill factories with tiles from the tile bag
        void fillFactories(TileBag* tileBag);

        // Return the factory of the index
        std::vector<char>* getFactory(int index);

        // Return true if all factories are empty
        bool isEmpty();
    private:
        // Store 6 factories (vector) in an array
        std::array<std::vector<char>, FACTORYNUMBER> factories;
};