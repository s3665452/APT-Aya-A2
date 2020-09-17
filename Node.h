#ifndef NODE
#define NODE

#include "Tile.h"

class Node {
public:	
    Node(Tile* tilebag, Node* next);
	Node(Node& other);

    Tile* tilebag;
    Node* next;
};

#endif //NODE