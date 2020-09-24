#include "LinkedList.h"

#ifndef TILEBAG
#define TILEBAG

class TileBag {
public:
    TileBag(char* tileBagOrder);
    TileBag();
    TileBag(const TileBag& other);
    TileBag(TileBag&& other);
    ~TileBag();
    unsigned int size() const;
    char front() const;
    void enqueue(char tile);
    void dequeue();
    void clear();

private:
    LinkedList queue;
};

#endif //TILEBAG