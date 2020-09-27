#include <string>
#include "Types.h"
#include "TileBag.h"

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

    // Return true is the tile in the mosaic has been covered
    bool tileCovered(int rowNum, char colour) const;

    // Empty stores, till the wall, move the rest to the tile bag
    // Can only be called when 'F' is not in the broken
    void tileTheWall(TileBag* tileBag);

    // Calculate score according to the location of a newly added tile
    void addScore(int y, int x);

    // Empty broken, deduct points
    void emptyBroken(TileBag* tileBag);


private:

    std::string name;
    int score;
    int containFirst;
};











#endif //PLAYER