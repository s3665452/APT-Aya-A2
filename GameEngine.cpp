#include "GameEngine.h"

GameEngine::GameEngine() {
    this->currentTurn = 0;
    this->playerA = nullptr;
    this->playerB = nullptr;
    this->tileBag = nullptr;
}

GameEngine::~GameEngine() {
    delete playerA;
    delete playerB;
    delete tileBag;
}

void GameEngine::NewGame() {
    
}