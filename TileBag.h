#ifndef LINKEDLIST
#define LINKEDLIST

#include <vector>
#include <iostream>

#include "Node.h"

class TileBag {
public:
   TileBag(char* tileBagOrder);
   TileBag();
   ~TileBag();

   int size();

   char getFirstTile();

    /**
    * Add the tile to the front of the Linked List
    */
   void addTile_front(char tile);

    /**
    * Add the tile to the back of the Linked List
    */
   void addTile_back(char tile);

    /**
    * Remove the tile at the front of the Linked List
    */
   bool removeTile_front();

    /**
    * Removes all tiles from the Linked List
    */
   void clear(); 
   void printAll();

private:
   Node* head;
   int length;
};

#endif //LINKEDLIST

