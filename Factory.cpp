#include <vector>
#include "Tile.h"

class Factory{
    private:
        std::vector<Tile> tiles;
    public:
        void add(Tile&);
        Tile& remove();
}

void add(){
    tiles.push_back(Tile);
}

Tile& remove(){
    for(int i=0;i<tiles.size();++i){
        tiles[i].clear();
    }
}
