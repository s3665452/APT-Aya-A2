#include "TileBag.h"


TileBag::TileBag(const char* tileBagOrder){
    int i = 0;
    while(tileBagOrder[i] != '\0' && i != TILEBAG_MAX_SIZE){
        enqueue(tileBagOrder[i]);
        i++;
    }
}


TileBag::TileBag(const TileBag& other) {
    queue = other.queue;
}

TileBag::TileBag(TileBag&& other) {
    queue = other.queue;
}

TileBag::~TileBag() {
    clear();
}

unsigned int TileBag::size() const {
    return queue.size();
}

char TileBag::front() const {
    return queue.getFront();
}

void TileBag::enqueue(char tile) {
    queue.add_back(tile);
}

void TileBag::dequeue() {
    queue.removeFront();
}

void TileBag::clear() {
    queue.clear();
}