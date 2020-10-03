#include "Types.h"

#ifndef LINKEDLIST
#define LINKEDLIST

#include <iostream>

template<typename T>
class Node {
public:	
    Node(T value, Node* next, Node* prev);
	Node(Node& other);
    
    // Value stored in the node
    T value;

    // A pointer to the next node
    Node* next;

    // A pointer to the previous node
    Node* prev;
};

template<typename T>
class LinkedList {
public:
    // Constructor
   LinkedList();

   // Deconstructor
   ~LinkedList();

   int size() const;

   T getFront() const;

    /**
    * Add the tile to the back of the Linked List
    */
   void add_back(T value);

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
   Node<T>* head;
   Node<T>* tile;
   int length;
};


//Constructor of Node
template<typename T>
Node<T>::Node(T value, Node<T>* next, Node<T>* prev) {
    this->value = value;
    this->next = next;
    this->prev = prev;
}

//Copy constructor of the node
template<typename T>
Node<T>::Node(Node<T>& other) {
    this->value = other.value;
    this->next = new Node<T>(other.next);
    this->prev = new Node<T>(other.prev);
}


//Constructor of TileBag
template<typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    tile = nullptr;
    length = 0;
}

// template<typename T>
// LinkedList<T>::LinkedList(LinkedList<T>& other) {

// }

//Deconstructor
template<typename T>
LinkedList<T>::~LinkedList(){
    clear();
}

template<typename T>
int LinkedList<T>::size() const{
    return this->length;
}

//get the first value
template<typename T>
T LinkedList<T>::getFront() const{
    T ret = T();
    if(head != nullptr) {
    ret = head->value;
    } 
    return ret;
}

//remove the tile at the front of the list
template<typename T>
void LinkedList<T>::removeFront() {
    if(head != nullptr) {
        Node<T>* current = head;
        if(head->next != nullptr) {
            head = head->next;
            head->prev = nullptr;
        }
        this->length -= 1;
        delete current;
    }
}


//add the tile at the back of the list
template<typename T>
void LinkedList<T>::add_back(T value){
    Node<T>* newNode = new Node<T>(value, nullptr, tile);
    if(tile != nullptr) {
      Node<T>* curr = tile;
      curr->next = newNode;
      tile = newNode;
      this->length++;
    } else {
        head = newNode;
        tile = newNode;
        this->length++;
   }   
}


//delete the list
template<typename T>
void LinkedList<T>::clear(){
    if(head != nullptr) {
        Node<T>* curr = head;
        while(curr->next != nullptr) {
            Node<T>* toDelete = curr;
            curr = curr->next;
            delete toDelete;
        }
        delete curr;
    }
    this->length = 0;
}

// Print all tiles (for testing)
template<typename T>
void LinkedList<T>::printAll() {
    Node<T>* curr = head;
    while(curr->next != nullptr){
        std::cout << curr->tile ;
        curr = curr->next;
    }
    std::cout << curr->tile << std::endl;
}

#endif //LINKEDLIST

