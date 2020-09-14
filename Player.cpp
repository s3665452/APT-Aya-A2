#include "Player.h"
#include <memory>

Player::Player(std::string playerName) {
    this->name = playerName;
    this->score = 0;

    this->store = new char*[MOSAIC_DIM];
    for (int i = 0; i != MOSAIC_DIM; ++i) {
        store[i] = new char[i+1];
        for (int n = 0; n != i+1; ++n) {
            store[i][n] = '.';
        }
    }

    for (int i = 0; i != MOSAIC_DIM; ++i){
        for (int n = 0; n != MOSAIC_DIM; ++n){
            board[i][n] = '.';
        }
    }
}

Player::~Player() {
    for (int i = 0; i != MOSAIC_DIM; ++i) {
        delete store[i];
    }
    delete store;

}

std::string Player::getName() {
    return this->name;
}