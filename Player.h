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

    // Return the scoure of the player
    int getScore() const;

    // Return the name of the palyer
    std::string getName() const;

    void printInfo();

    // Return true is selected store is full
    bool isFull(int storeNum) const;

    // Return occupied colour of the selected store
    char storeColour(int storeNum) const;

    // Return true is the tile in the mosaic has been filled
    bool tileFilled(int rowNum, char colour) const;



private:

    std::string name;
    int score;
    int containFirst;
};











#endif //PLAYER