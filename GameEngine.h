// To be implemented on week 9

#include "Player.h"
#include "TileBag.h"
#include "string"
#include "Factories.h"

#ifndef GAMEENGINE
#define GAMEENGINE

class GameEngine {
public:
    //Constructor
    GameEngine();
    //Deconstructor
    ~GameEngine();
    void newGame(bool startgame);
    void loadGame();
    void printFactories();
    void printMosaic(Player& player);

private:
    int currentTurn;
    Player* playerA;
    Player* playerB;
    TileBag* tileBag;
    Factories* factories;
};

#endif //GAMEENGINE