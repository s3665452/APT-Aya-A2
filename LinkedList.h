#include "Types.h"

#ifndef LINKEDLIST
#define LINKEDLIST


template<typename T>
class Node {
public:	
    // Constructor for Node
    Node(T value, Node* next, Node* prev);

    // Copy constructor
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

    // Return size of the linked list
   int size() const;

    // Return the first value 
   T getFront() const;

    // Return the value in the index
   T get(int index) const;

    // Add the tile to the back of the Linked List   
   void add_back(T value);

    // Remove the tile at the front of the Linked List
   void removeFront();
    
    // Removes all tiles from the Linked List
   void clear(); 

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

//Deconstructor
template<typename T>
LinkedList<T>::~LinkedList(){
    clear();
}

// Return the size of the linked list
template<typename T>
int LinkedList<T>::size() const{
    return this->length;
}

// Return the value in the index
template<typename T>
T LinkedList<T>::get(int index) const {
    T ret = T();
    Node<T>* current = head;
    for(int i = 0; i < index; i++) {
        current = current->next;
    }
    ret = current->value;
    return ret;
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


#endif //LINKEDLIST

