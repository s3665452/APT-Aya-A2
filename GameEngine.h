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
    void loadGame(std::string filename);
    void printFactories() const;
    void printMosaic(Player* player) const;
    void getCommand();
    void selectTile(int factoryNum, char tile, int storeNum);
    void changePlayer();

    //saved Game
    void saveGame();

    // Play a single round
    void playOneRound();

    // Set the player who has 'F' to be current player, move 'F' to the centre
    void setFirstPlayer();

    // End game result
    void printResult();

private:
    int currentTurn;
    Player* currentPlayer;
    Player* playerA;
    Player* playerB;
    TileBag* tileBag;
    Factories* factories;
};

#endif //GAMEENGINE