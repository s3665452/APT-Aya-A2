#include "Types.h"

#ifndef LINKEDLIST
#define LINKEDLIST

#include <vector>
#include <iostream>

#include "Node.h"

class LinkedList {
public:
   LinkedList(char* tileBagOrder);
   LinkedList();
   ~LinkedList();

   int size() const;

   char getFront() const;

    /**
    * Add the tile to the back of the Linked List
    */
   void addTile_back(char tile);

    /**
    * Remove the tile at the front of the Linked List
    */
   void removeFront();

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

