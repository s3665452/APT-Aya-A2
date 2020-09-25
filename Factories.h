#include <vector>
#include <array>
#include "TileBag.h"

#define FACTORYSIZE 5
#define FACTORYNUMBER 6

class Factories {
    public:
        Factories(TileBag& tileBag);
        ~Factories();
        void fillFactories(TileBag& tileBag);
        std::vector<char>* getFactory(int index);
        bool isEmpty();
    private:
        // Create 6 factories in an array
        std::array<std::vector<char>, FACTORYNUMBER> factories;

};