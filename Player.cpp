#include "Player.h"
#include "Types.h"
#include <memory>
#include <iostream>

Player::Player(std::string playerName) {
    this->name = playerName;
    this->score = 0;
    // Allocate memory for store, fill it with '.'
    this->store = new char*[MOSAIC_DIM];
    for (int i = 0; i != MOSAIC_DIM; ++i) {
        store[i] = new char[i+1];
        for (int n = 0; n != i+1; ++n) {
            store[i][n] = '.';
        }
    }
    // Fill the board with '.'
    int index = 0;
    for (int i = 0; i != MOSAIC_DIM; ++i){
        for (int n = 0; n != MOSAIC_DIM; ++n){
            board[i][n].first = MOSAIC_ORDER[index];
            board[i][n].second = '.';
            index += 1;
        }
    }
}


Player::~Player() {
    for (int i = 0; i != MOSAIC_DIM; ++i) {
        delete[] store[i];
    }
    delete store;
}


Player::Player(Player& other) {
    this->store = new char*[MOSAIC_DIM];
    for (int i = 0; i != MOSAIC_DIM; ++i) {
        store[i] = new char[i+1];
        for (int n = 0; n != i+1; ++n) {
            store[i][n] = other.store[i][n];
        }
    }

    for (int i = 0; i != MOSAIC_DIM; ++i){
        for (int n = 0; n != MOSAIC_DIM; ++n){
            board[i][n].first = other.board[i][n].first;
            board[i][n].second = other.board[i][n].second;
        }
    }
    this->broken = other.broken;
    this->name = other.name;
    this->score = other.score;
}


Player::Player(Player&& other) {
    this->store = new char*[MOSAIC_DIM];
    for (int i = 0; i != MOSAIC_DIM; ++i) {
        store[i] = new char[i+1];
        for (int n = 0; n != i+1; ++n) {
            store[i][n] = other.store[i][n];
        }
    }

    for (int i = 0; i != MOSAIC_DIM; ++i){
        for (int n = 0; n != MOSAIC_DIM; ++n){
            board[i][n].first = other.board[i][n].first;
            board[i][n].second = other.board[i][n].second;
        }
    }
    this->broken = other.broken;
    this->name = other.name;
    this->score = other.score;
}


std::string Player::getName() const {
    return this->name;
}


int Player::getScore() const {
    return this->score;
}


bool Player::isFull(int storeNum) const{
    bool ret = false;
    // Check if the last element in a row is '.'
    if(store[storeNum - 1][storeNum - 1] != '.') {
        ret = true;
    }
    return ret;
}


char Player::storeColour(int storeNum) const{
    return store[storeNum-1][0];
}


bool Player::tileCovered(int rowNum, char colour) const{
    bool ret = false;
    int i = 0;
    // Find the position of the colour in the row
    while(board[rowNum - 1][i].first != colour) {
        i += 1;
    }
    if(board[rowNum - 1][i].second != '.') {
        ret = true;
    }
    return ret;
}


void Player::tileTheWall(TileBag* tileBag) {
    for(int i = 0; i < MOSAIC_DIM; i++) {
        if(isFull(i + 1)) {
            // Find and cover the tile spot on the board
            int n = 0;
            while(board[i][n].first != storeColour(i + 1)) {
                n += 1;
            }
            board[i][n].second = storeColour(i + 1);
            // Calculate and add points
            addScore(i, n);
            // "Move" tiles to the tile bag
            store[i][0] = '.';
            for(int index = 1; index < i + 1; index++) {
                tileBag->enqueue(store[i][index]);
                store[i][index] = '.';
            }
        }
    }
    emptyBroken(tileBag);
}


void Player::addScore(int y, int x) {
    int score = 1;
    // Calculate horizontal points
    int i = 1;
    while(x + i < MOSAIC_DIM && board[y][x + i].second != '.') {
        score += 1;
        i += 1;
    }
    i = 1;
    while(x - i > -1 && board[y][x - i].second != '.') {
        score += 1;
        i += 1;
    }
    // Calculate vertical points
    i = 1;
    if((y + i < MOSAIC_DIM && board[y + i][x].second != '.') || (y - i > -1 && board[y - i][x].second != '.')) {
        if(score > 1) {
            score += 1;
        }
    }
    while(y + i < MOSAIC_DIM && board[y + i][x].second != '.') {
        score += 1;
        i += 1;
    }
    i = 1;
    while(y - i > -1 && board[y - i][x].second != '.') {
        score += 1;
        i += 1;
    }
    // Add score to player score
    this->score += score;
}


void Player::emptyBroken(TileBag* tileBag) {
    // Deduct points from tiles in the broken
    if(BROKEN_DEDUCTION[broken.size()] > this->score) {
        this->score = 0;
    }
    else {
        this->score -= BROKEN_DEDUCTION[broken.size()];
    }
    for(long unsigned int n = 0; n < broken.size(); n++) {
        if(broken[n] != 'F') {
        tileBag->enqueue(broken[n]);
        }
    }
    broken.clear();
}