#include <vector>
#include "TileBag.h"

class Factory {
    public:
        Factory();
        ~Factory();
        void add(char tileColor);
        void remove();
        int getSize();
        void setIsFactory(bool isFactory);
        bool getIsFactory ();
        std::string printTiles();
    private:
        std::vector<char> * factoryTiles;
        bool isFactory;


};