#include <vector>
#include "TileBag.h"

class Factory {
    public:
        Factory();
        ~Factory();
        Factory(const Factory&);
        void add(TileBag);
        void remove(int i);
        int getSize();
    private:
        std::vector<TileBag> * allTiles;
};