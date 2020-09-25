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
    void saveGame();
    void printFactories();
    void printMosaic(Player& player);

    // player end of turn
    bool endTurn(Factories* factories, int num);

private:
    int currentTurn;
    //int numFac;
    //int numMos;
    Player* playerA;
    Player* playerB;
    TileBag* tileBag;
    Factories* factories;
};

#endif //GAMEENGINE