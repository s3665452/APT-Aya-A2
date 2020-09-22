#include "GameEngine.h"

GameEngine::GameEngine() {
    this->currentTurn = 0;
    this->playerA = nullptr;
    this->playerB = nullptr;
    this->tileBag = new TileBag();
    this->factories = new Factories(*tileBag);
}

GameEngine::~GameEngine() {
    delete playerA;
    delete playerB;
    delete tileBag;
    delete factories;
}

void GameEngine::newGame() {
    std::string playerNameA;
    std::string playerNameB;
   //Testing
   this->tileBag->printAll();

    std::cout << std::endl;

    std::cout << "Starting a New Game" << std::endl << std::endl;
    std::cout << "Enter a name for player 1" << std::endl << "> ";
    std::cin >> playerNameA;
    std::cout << std::endl << "Enter a name for player 2" << std::endl << "> ";
    std::cin >> playerNameB;

    this->playerA = new Player(playerNameA);
    this->playerB = new Player(playerNameB);
    std::cout << std::endl << "Let's Play!" << std::endl;

    std::cout << playerA->getName() << std::endl;
    std::cout << playerB->getName() << std::endl;
     printMosaic(*playerA);
    // printMosaic(*playerB);
    
}

void GameEngine::printFactories() {

}

// Print mosaic for a player
void GameEngine::printMosaic(Player& player) {
    std::cout << std::endl << "Mosaic for " << player.getName() << ":" << std::endl;
    for(int i = 0; i < MOSAIC_DIM; i++) {
        // Print row number
        std::cout << i + 1 << ":";
        // Print white space before mosaic row
        for(int n = MOSAIC_DIM - i - 1; n > 0; n--) {
            std::cout << "  ";
        }
        // Print store row
        for(int n = 0; n < i + 1; n++) {
            std::cout << " " << player.store[i][n];  
        }
        std::cout << " ||";
        // Print board row
        for(int n = 0; n < MOSAIC_DIM; n++) {
            std::cout << " " << player.board[i][n];
        }
        std::cout << std::endl;
       
    }
    // Print broken
    std::cout << "broken:";
    int brokenSize = player.broken.size();
    for(int i = 0; i < brokenSize; i++) {
        std::cout << " " << player.broken[i]; 
    }
    std::cout << std::endl << std::endl;
}