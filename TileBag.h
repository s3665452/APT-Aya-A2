#include "LinkedList.h"

#ifndef TILEBAG
#define TILEBAG

class TileBag {
public:
    //Constructor of TileBag
    TileBag(const char* tileBagOrder);

    // Copy constructor
    TileBag(const TileBag& other);

    // Move constructor
    TileBag(TileBag&& other);

    // Deconstructor
    ~TileBag();

    // Return size of the tile bag
    unsigned int size() const;

    // Return the first element of the tile bag
    char front() const;

    // Add an tile to to back of the tile bag
    void enqueue(char tile);

    // Remove the first element
    void dequeue();

    // Remove all element
    void clear();

private:
    // Linked list queue
    LinkedList<char> queue;
};

#endif //TILEBAG