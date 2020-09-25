#include <string>
#include "Types.h"

#ifndef PLAYER
#define PLAYER

class Player {
public:
    Store store;
    Board board;
    Broken broken;
    // Constructor /Deconstructor
    Player(std::string playerName);
    ~Player();

    // Copy Constructor
    Player(Player& other);

    // Move Constructor
    Player(Player&& other);

    int getScore();
    std::string getName();
    void printInfo();


    // turn for the player
    bool isTheTurn();
    // return true if mosiac's player contain the first player tile 
    bool isFirst(); 

private:

    std::string name;
    int score;
    int currentTurn;
    int containFirst;
};











#endif //PLAYER