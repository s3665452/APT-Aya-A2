#include <string>
#include "Types.h"

#ifndef PLAYER
#define PLAYER

class Player {
public:
    // Constructor /Deconstructor
    Player(std::string playerName);
    ~Player();

    // Copy Constructor
    Player(Player& other);

    // Move Constructor
    Player(Player&& other);

    int getScore();
    std::string getName();

private:

    std::string name;
    int score;
    Store store;
    Board board;
    Broken broken;


};











#endif //PLAYER