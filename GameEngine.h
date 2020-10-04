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

    // Whether it is in the testing mode
    bool testingMode;

    // Name of the file to be load
    std::string loadFileName;

private:
    // Number of the current turn
    int currentTurn;
    // Pointer to the current player
    Player* currentPlayer;
    // Pointer to player A
    Player* playerA;
    // Pointer to player B
    Player* playerB;
    // Pointer to the tile bag of the game
    TileBag* tileBag;
    // Pointer to factories
    Factories* factories;
    // Saved tile bag order, player names and commands
    LinkedList<std::string> saved;

    // Print the Factories
    void printFactories() const;

    // Print the mosaic of the player
    void printMosaic(Player* player) const;

    // Get a line of command from user
    void getCommand();

    // Select all tiles of the colour in the factory, put them in the store of the player
    void selectTile(int factoryNum, char tile, int storeNum);

    // Change the current player
    void changePlayer();

    // Play a single round
    void playOneRound();

    // Set the player who has 'F' to be current player, move 'F' to the centre
    void setFirstPlayer();

    // End game result
    void printResult();

    // Save game to a file
    void saveGame(std::string filename);

    // Clean up memories
    void cleanUp();
};


#endif //GAMEENGINE