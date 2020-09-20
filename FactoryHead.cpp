#include "Factory.h"
#include "TileBag.h"


void createFactoryHeader() {


    TileBag t = TileBag();
    Factory f1 = Factory();

    for(int i=0; i<4; i++){
        f1.add(t.getFirstTile());
    }

    Factory f2 = Factory();

    for(int i=0; i<4; i++){
        f2.add(t.getFirstTile());
    }
    Factory f3 = Factory();

    for(int i=0; i<4; i++){
        f3.add(t.getFirstTile());
    }

    Factory f4 = Factory();

    for(int i=0; i<4; i++){
        f4.add(t.getFirstTile());
    }
    Factory f5 = Factory();

    for(int i=0; i<4; i++){
        f5.add(t.getFirstTile());
    }

    Factory cf = Factory();
    cf.setIsFactory(true);

    //Testing 
    f1.remove();
    f1.printTiles();

    f2.printTiles();

}