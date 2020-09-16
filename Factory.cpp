#include <vector>

class Factory{
    private:
        std::vector<Tile> tiles;
    public:
        void add(Tile&);
        Tile& remove();
}

void add(Tile&){
    tiles.push_back(Tile&);
}