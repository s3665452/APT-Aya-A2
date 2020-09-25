// To be implemented on week 9

#include "Player.h"
#include "TileBag.h"
#include "string"
#include "Factories.h"

#ifndef GAMEENGINE
#define GAMEENGINE

class GameEngine {
public:
    // Constructor
    GameEngine();
    // Deconstructor
    ~GameEngine();
    // Start a new game
    void newGame(bool startgame);
    // Load a saved game
    void loadGame();
    void printFactories() const;
    void printMosaic(Player* player) const;
    void getUserInput(Player* player);
    void selectTile(Player* player, int factoryNum, char tile, int storeNum);

    //saved Game
    void saveGame();

    void playerTurn();

    // player end of turn
    bool endTurn(Factories* factories, int num);

private:
    int currentTurn;
    int numFac;
    //int numMos;
    Player* playerA;
    Player* playerB;
    TileBag* tileBag;
    Factories* factories;
};

#endif //GAMEENGINE