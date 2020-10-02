#include "Player.h"
#include "TileBag.h"
#include <string>
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
    void newGame();
    // Load a saved game
    void loadGame();
    // Print the Factories
    void printFactories() const;
    void printMosaic(Player* player) const;
    void getCommand();
    void selectTile(int factoryNum, char tile, int storeNum);
    void changePlayer();

    //saved Game
    void saveGame(std::string filename);

    // Play a single round
    void playOneRound();

    // Set the player who has 'F' to be current player, move 'F' to the centre
    void setFirstPlayer();

    // End game result
    void printResult();

    // Whether it is in the testing mode
    bool testingMode;

    // Name of the file to be load
    std::string loadFileName;

private:
    int currentTurn;
    Player* currentPlayer;
    Player* playerA;
    Player* playerB;
    TileBag* tileBag;
    Factories* factories;
    LinkedList<std::string> saved;
};

#endif //GAMEENGINE