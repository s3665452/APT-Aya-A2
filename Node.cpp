#include "Node.h"

//Constructor of Node
Node::Node(Tile* tilebag, Node* next) {
    this->tilebag = tilebag;
    this->next = next;
}

//Copy constructor of the node
Node::Node(Node& other) {
    this->tilebag = other.tilebag;
    this->next = other.next;
}
