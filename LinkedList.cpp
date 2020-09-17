#include "LinkedList.h"

#include <string>
#include <iostream>

//Constructor of LinkedList
LinkedList::LinkedList(){
    head = nullptr;
    length = 0;
}

//Deconstructor
LinkedList::~LinkedList(){
    clear();
}

int LinkedList::size(){
    return this->length;
}

//get the first tile in the tilebag
Tile* LinkedList::getFirstTile(){
    Tile* retTile = nullptr;

    if(retTile != nullptr) {
    Node* curr = head;
    head = curr->next;
    this->length--;

    return curr->tilebag;
   } else {
    return retTile;
    }   
}

// add a tile infront of the list
void LinkedList::addTile_front(Tile* tilebag){
    Node* node = new Node(tilebag,head);
    node->tilebag = tilebag;
    node->next = head;
    head = node;
    this->length++;
}

//add the tile at the back of the list
void LinkedList::addTile_back(Tile* tilebag){
    if(head != nullptr) {
      Node* toAdd  = head;
      while(toAdd->next != nullptr) {
          toAdd = toAdd->next;
      }
      toAdd->next = new Node(tilebag, nullptr);
      this->length++;
      toAdd = nullptr;
  } else {
        head = new Node(tilebag, nullptr);
        this->length++;
   }   
}

//remove an element in the list
bool LinkedList::removeTile(Tile* tilebag){
    Node* toDelete = head;
    if(head->tilebag->getColour() == tilebag->getColour()){
        head = head->next;
        delete toDelete->tilebag;
        delete toDelete;
        this->length--;
        return true;
    }   
    for(int i = 0; i < this->length-1; ++i) {    
        if(toDelete->next->tilebag->getColour() == tilebag->getColour()){
            toDelete ->next = toDelete;
            toDelete = toDelete->next->next;
            this->length--;
            delete toDelete->tilebag;
            delete toDelete;
            return true;
        }
        toDelete  = toDelete->next;
    }    
    return false;
}

//delete the list
void LinkedList::clear(){
    if(head != nullptr) {
        Node* checkTheNode = head;
        while(checkTheNode != nullptr) {
            Node* next = checkTheNode->next;
            checkTheNode = nullptr;
            delete checkTheNode;
            checkTheNode = next;
        }
        delete checkTheNode;
    }
    this->length = 0;
}



