#include "Node.h"

//Constructor of Node
Node::Node(char tile, Node* next) {
    this->tile = tile;
    this->next = next;
}

//Copy constructor of the node
Node::Node(Node& other) {
    this->tile = other.tile;
    this->next = other.next;
}
