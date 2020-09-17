#ifndef LINKEDLIST
#define LINKEDLIST

#include <vector>
#include <iostream>
#include "ColorTile.h"

#include "Node.h"

class LinkedList {
public:
   LinkedList();
   ~LinkedList();

   int size();

   Tile* getFirstTile();

    /**
    * Add the tile to the front of the Linked List
    */
   void addTile_front(Tile* tilebag);

    /**
    * Add the tile to the back of the Linked List
    */
   void addTile_back(Tile* tilebag);

    /**
    * Remove the tile at the front of the Linked List
    */
   bool removeTile(Tile* tilebag);

    /**
    * Removes all tiles from the Linked List
    */
   void clear(); 

private:
   Node* head;
   int length;
};

#endif //LINKEDLIST

