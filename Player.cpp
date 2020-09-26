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

    int index = 0;
    for (int i = 0; i != MOSAIC_DIM; ++i){
        for (int n = 0; n != MOSAIC_DIM; ++n){
          //   std::cout << "board " << i << n; 
            board[i][n].first = MOSAIC_ORDER[index];
            board[i][n].second = '.';
            index += 1;
        }
    }
}

Player::~Player() {
    for (int i = 0; i != MOSAIC_DIM; ++i) {
        delete store[i];
    }
    delete store;

}

std::string Player::getName() const {
    return this->name;
}

int Player::getScore() const {
    return this->score;
}

void Player::printInfo() {
    std::cout <<"Name: "<< this->name << std::endl;
    std::cout <<"Score: "<< this->score << std::endl;
    std::cout << std::endl;
}

bool Player::isFull(int storeNum) const{
    bool ret = false;
    if(store[storeNum - 1][storeNum - 1] != '.') {
        ret = true;
    }
    return ret;
}

char Player::storeColour(int storeNum) const{
  //  std::cout << "Store colour: " << store[storeNum-1][0] << std::endl;
    return store[storeNum-1][0];
}

bool Player::tileCovered(int rowNum, char colour) const{
    bool ret = false;
    int i = 0;
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
                // std::cout << storeColour(i + 1) << std::endl;
                // std::cout << "board " << i << n << ": ";
                // std::cout << board[i][n].first << std::endl;
                n += 1;
            }
           // std::cout << "Board " << i << n << "set to " << storeColour(i + 1) << std::endl;
            board[i][n].second = storeColour(i + 1);
            
            // Set the first tile in the store to empty, "move" the rest to the tile bag
            store[i][0] = '.';
            for(int index = 1; index < i + 1; index++) {
                // std::cout << "enqueue " << i << index;
                // std::cout << store[i][index] << std::endl;
                tileBag->enqueue(store[i][index]);
                store[i][index] = '.';
            }
        }

        for(long unsigned int n = 0; n < broken.size(); n++) {
            // std::cout << "enqueue broken" << n;
            // std::cout << broken[n] << std::endl;
            tileBag->enqueue(broken[n]);
        }
        broken.clear();
    }
}