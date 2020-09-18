#include "TileBag.h"
#include "Types.h"

#include <string>
#include <iostream>

//Constructor of TileBag
TileBag::TileBag(char* tileBagOrder){
    head = nullptr;
    length = 0;

    int i = 0;
    while(tileBagOrder[i] != '\0' && i != TILEBAG_MAX_SIZE){
        addTile_back(tileBagOrder[i]);
        i++;
    }
}

//Default constructor of TileBag
TileBag::TileBag(){
    const char* tileBagOrder = TILEBAG_ORDER;
    head = nullptr;
    length = 0;

    int i = 0;
    while(tileBagOrder[i] != '\0' && i != TILEBAG_MAX_SIZE){
        addTile_back(tileBagOrder[i]);
        i++;
    }
}

//Deconstructor
TileBag::~TileBag(){
    clear();
}

int TileBag::size(){
    return this->length;
}

//get the first tile in the tilebag
char TileBag::getFirstTile(){
    char retTile = ' ';

    if(head != nullptr) {
    Node* curr = new Node(*head);
    head = head->next;
    this->length--;

    retTile = curr->tile;
    delete curr;
    } 
    return retTile;
}


//add the tile at the back of the list
void TileBag::addTile_back(char tile){
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
void TileBag::clear(){
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
void TileBag::printAll() {
    Node* curr = head;
    while(curr->next != nullptr){
        std::cout << curr->tile ;
        curr = curr->next;
    }
    std::cout << curr->tile << std::endl;
}


