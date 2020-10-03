#include <string>
#include "Types.h"
#include "TileBag.h"

#ifndef PLAYER
#define PLAYER

class Player {
public:
    // To store tiles selected from factories
    Store store;

    // Player mosaic
    Board board;

    // To store broken tiles
    Broken broken;

    // Constructor /Deconstructor
    Player(std::string playerName);
    ~Player();

    // Copy Constructor
    Player(Player& other);

    // Move Constructor
    Player(Player&& other);

    // Return the score of the player
    int getScore() const;

    // Return the name of the player
    std::string getName() const;

    // Return true is selected store is full
    bool isFull(int storeNum) const;

    // Return occupied colour of the selected store
    char storeColour(int storeNum) const;

    // Return true is the tile in the mosaic has been covered
    bool tileCovered(int rowNum, char colour) const;

    // Empty stores, till the wall, move the rest to the tile bag
    void tileTheWall(TileBag* tileBag);

    // Calculate score according to the location of a newly added tile
    void addScore(int y, int x);

    // Empty broken, deduct points
    void emptyBroken(TileBag* tileBag);


private:
    // Name of the player
    std::string name;
    
    // Score of the player
    int score;
};


#endif //PLAYER