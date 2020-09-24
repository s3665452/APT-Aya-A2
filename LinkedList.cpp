#include "LinkedList.h"

#include <string>
#include <iostream>

//Constructor of TileBag
LinkedList::LinkedList(){
    head = nullptr;
    length = 0;
}

//Deconstructor
LinkedList::~LinkedList(){
    clear();
}

int LinkedList::size() const{
    return this->length;
}

//get the first tile in the tilebag
char LinkedList::getFront() const{
    char retTile = ' ';
    if(head != nullptr) {
    retTile = head->tile;
    } 
    return retTile;
}

//remove the tile at the front of the list
void LinkedList::removeFront() {
    if(head != nullptr) {
        Node* current = head;
        head = head->next;
        delete current;
    }
}


//add the tile at the back of the list
void LinkedList::addTile_back(char tile){
    Node* newNode = new Node(tile, nullptr);
    if(head != nullptr) {
      Node* curr = head;
      
      while(curr->next != nullptr) {
          curr = curr->next;
      }
      curr->next = newNode;
      this->length++;

  } else {
        head = newNode;
        this->length++;
   }   
}


//delete the list
void LinkedList::clear(){
    if(head != nullptr) {
        Node* curr = head;
        while(curr->next != nullptr) {
            Node* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
        delete curr;
    }
    this->length = 0;
}

// Print all tiles (for testing)
void LinkedList::printAll() {
    Node* curr = head;
    while(curr->next != nullptr){
        std::cout << curr->tile ;
        curr = curr->next;
    }
    std::cout << curr->tile << std::endl;
}


