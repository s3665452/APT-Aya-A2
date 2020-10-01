#include "LinkedList.h"

#ifndef TILEBAG
#define TILEBAG

class TileBag {
public:
    TileBag(const char* tileBagOrder);
    TileBag(const TileBag& other);
    TileBag(TileBag&& other);
    ~TileBag();
    unsigned int size() const;
    char front() const;
    void enqueue(char tile);
    void dequeue();
    void clear();

private:
    LinkedList<char> queue;
};

#endif //TILEBAG