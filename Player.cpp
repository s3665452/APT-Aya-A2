#include "Player.h"
#include <memory>
#include <iostream>

Player::Player(std::string playerName) {
    this->name = playerName;
    this->score = 0;

    this->store = new char*[MOSAIC_DIM];
    for (int i = 0; i != MOSAIC_DIM; ++i) {
        store[i] = new char[i+1];
        for (int n = 0; n != i+1; ++n) {
           // std::cout << "store " << i << n; 
            store[i][n] = '.';
        }
    }

    for (int i = 0; i != MOSAIC_DIM; ++i){
        for (int n = 0; n != MOSAIC_DIM; ++n){
          //   std::cout << "board " << i << n; 
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

int Player::getScore() {
    return this->score;
}

void Player::printInfo() {
    std::cout <<"Name: "<< this->name << std::endl;
    std::cout <<"Score: "<< this->score << std::endl;
    std::cout << std::endl;
}

bool Player::isTheTurn(){
    return this->currentTurn;
}

bool Player::isFirst(){
     return this->containFirst;
}