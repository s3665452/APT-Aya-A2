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
    void getCommand();
    void selectTile(int factoryNum, char tile, int storeNum);
    void changePlayer();
    void moveTilesToMosaic();

    //saved Game
    void saveGame();

    void playerTurn();

private:
    int currentTurn;
    Player* currentPlayer;
    Player* playerA;
    Player* playerB;
    TileBag* tileBag;
    Factories* factories;
};

#endif //GAMEENGINE