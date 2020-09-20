// To be implemented on week 9

#include "Player.h"
#include "TileBag.h"
#include "string"

#ifndef GAMEENGINE
#define GAMEENGINE

class GameEngine {
public:
    //Constructor
    GameEngine();
    //Deconstructor
    ~GameEngine();
    void NewGame();
    void LoadGame();

private:
    int currentTurn;
    Player* playerA;
    Player* playerB;
    TileBag* tileBag;
};

#endif //GAMEENGINE