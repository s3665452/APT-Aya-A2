#include "Types.h"

#ifndef LINKEDLIST
#define LINKEDLIST

#include <iostream>

template<typename T>
class Node {
public:	
    Node(T value, Node* next);
	Node(Node& other);
    
    T value;
    Node* next;
};

template<typename T>
class LinkedList {
public:
   LinkedList();
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
   int length;
};


//Constructor of Node
template<typename T>
Node<T>::Node(T value, Node* next) {
    this->value = value;
    this->next = next;
}

//Copy constructor of the node
template<typename T>
Node<T>::Node(Node<T>& other) {
    this->value = other.value;
    this->next = other.next;
}


//Constructor of TileBag
template<typename T>
LinkedList<T>::LinkedList(){
    head = nullptr;
    length = 0;
}

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
        head = head->next;
        this->length -= 1;
        delete current;
    }
}


//add the tile at the back of the list
template<typename T>
void LinkedList<T>::add_back(T value){
    Node<T>* newNode = new Node<T>(value, nullptr);
    if(head != nullptr) {
      Node<T>* curr = head;
      
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

