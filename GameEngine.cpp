#include "GameEngine.h"
#include "Types.h"
#include <sstream>

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

void GameEngine::loadGame(){

}

void GameEngine::saveGame(){

}

void GameEngine::newGame(bool startgame) {
    std::string playerNameA;
    std::string playerNameB;

    //Testing
    //this->tileBag->printAll();

    //bool loadGame = false;
    // start a new game
    if (startgame == true){
        //if the game is a new game then initialize
        std::cout << "Starting a New Game" << std::endl << std::endl;
        std::cout << "Enter a name for player 1" << std::endl << "> ";
        std::cin >> playerNameA;
        std::cout << std::endl << "Enter a name for player 2" << std::endl << "> ";
        std::cin >> playerNameB;
        std::string dummy;
        getline(std::cin, dummy);
        this->playerA = new Player(playerNameA);
        this->playerB = new Player(playerNameB);
        std::cout << std::endl << "Let's Play!" << std::endl;

        std::cout << playerA->getName() << std::endl;
        std::cout << playerB->getName() << std::endl;
    } else {
        //continue if the game is a load game
        std::cout << "Azul game successfully loaded" << std::endl;
        std::cout <<  "<game play continues from here>"<< std::endl;
        std::cout << std::endl;
       // loadGame = true;
}
        std::cout << std::endl;
        std::cout << "=== Start Round ===";
        std::cout << std::endl;

        this->currentPlayer = playerA;
        //Test
        // printFactories();
        // printMosaic(playerA);
        // selectTile(1, 'U', 2);
        // changePlayer();
        // printFactories();
        // printMosaic(playerB);
        // selectTile(0, 'Y', 1);
        // getCommand();
        playerTurn();
}

void GameEngine::playerTurn(){
    while(!factories->isEmpty()) {
        //The turn run until the factories is empty
        printFactories();
        printMosaic(currentPlayer);
        getCommand();
        changePlayer();
    }

        delete factories;
        std::cout<<std::endl;
        std::cout<<"=== GAME OVER ===";
        std::cout<<std::endl;
                            
        // winner of the game
        std::cout << std::endl;
        std::string winner = " ";
        int score = 0;
        std::cout << "Final Scores: " << std::endl;
        std::cout << playerA->getName()<< ":" << playerA->getScore() << std::endl; 
        std::cout << playerB->getName()<< ":" << playerB->getScore() << std::endl; 

           if(playerA->getScore() > score) {
              score = playerA->getScore();
              winner = playerA->getName();
           } else if (playerB->getScore() > score) {
              score = playerB->getScore();
              winner = playerB->getName();
    }
    if(winner == " ") {
        std::cout << "Draw!" << std::endl;
    } else {
        std::cout << "Player " << winner <<" wins!"<< std::endl;
    }                                     
}

void GameEngine::printFactories() const {
    std::cout << "Factories:" << std::endl;
    for(int i = 0; i < FACTORYNUMBER; i++) {
        std::cout << i << ":";
        for(long unsigned int n = 0; n < factories->getFactory(i)->size(); n++) {
            std::cout << " " << (*factories->getFactory(i))[n];
        }
        std::cout << std::endl;
    }
}

// Print mosaic for a player
void GameEngine::printMosaic(Player* player) const {
    std::cout << std::endl << "Mosaic for " << player->getName() << ":" << std::endl;
    for(int i = 0; i < MOSAIC_DIM; i++) {
        // Print row number
        std::cout << i + 1 << ":";
        // Print white space before mosaic row
        for(int n = MOSAIC_DIM - i - 1; n > 0; n--) {
            std::cout << "  ";
        }
        // Print store row
        for(int n = 0; n < i + 1; n++) {
            std::cout << " " << player->store[i][n];  
        }
        std::cout << " ||";
        // Print board row
        for(int n = 0; n < MOSAIC_DIM; n++) {
            std::cout << " " << player->board[i][n];
        }
        std::cout << std::endl;
       
    }
    // Print broken
    std::cout << "broken:";
    int brokenSize = player->broken.size();
    for(int i = 0; i < brokenSize; i++) {
        std::cout << " " << player->broken[i]; 
    }
    std::cout << std::endl << std::endl;
}

// Select tiles to put in store
void GameEngine::selectTile(int factoryNum, char tile, int storeNum) {
    std::vector<char>* selectedFactory = factories->getFactory(factoryNum);
    char* selectedStore = currentPlayer->store[storeNum-1];
   
    long unsigned int i = 0;
    while( i < selectedFactory->size()) {
        // Put F to broken directly
        if((*selectedFactory)[i] == 'F') {
          //  std::cout << "Tile: " << "F" << std::endl;
            currentPlayer->broken.push_back('F');
            selectedFactory->erase(selectedFactory->begin() + i);
        }
        // If it is selected tile, put it to player store or broken
        else if ((*selectedFactory)[i] == tile) {
         //   std::cout << "Tile: " << tile << std::endl;
            // Iterate until find empty or reach the maximum size
            int n = 0;
            while(selectedStore[n] != '.' && n < storeNum) {
                n += 1;
            }
            // If there is a empty spot, put the tile in, otherwise put the tile to broken
            if(n < storeNum) {
                selectedStore[n] = tile;
            }
            else {
                currentPlayer->broken.push_back(tile);
            }   
            selectedFactory->erase(selectedFactory->begin() + i);
        }
        // If it is other tiles, put it to centre if selected factory is not centre
        else {
         //  std::cout << "Tile: " << (*selectedFactory)[i] << std::endl;
             if(factoryNum == 0) {
                i += 1;
             }
             else {
                 factories->getFactory(0)->push_back((*selectedFactory)[i]);
              //   std::cout << "pushed" << std::endl;
                 selectedFactory->erase(selectedFactory->begin() + i);
             }
        }
    }
}

void GameEngine::getCommand() {
    std::cout << "> ";

    std::string line;
    getline(std::cin, line);
    std::istringstream is(line);

    std::string turn;
    int factoryNum;
    char tile;
    int storeNum;

    is >> turn;
    is >> factoryNum;
    is >> tile;
    is >> storeNum;

    if(std::cin.eof()){
        exitGame();
    }

    std::cout << turn << std::endl;
    std::cout << factoryNum << std::endl;
    std::cout << tile << std::endl;
    std::cout << storeNum << std::endl;

    if(turn != "turn" || factoryNum < 0 || factoryNum > 5 || !isTile(tile) || storeNum < 1 || storeNum > 5 || !contains(factories->getFactory(factoryNum), tile)) {
        std::cout << "Invalid Input" << std::endl;
        getCommand();
    }

    selectTile(factoryNum, tile, storeNum);

}

// Change current player
void GameEngine::changePlayer() {
    if(this->currentPlayer == playerA) {
        this->currentPlayer = playerB;
    }
    else if(this->currentPlayer == playerB) {
        this->currentPlayer = playerA;
    }
}

void GameEngine::moveTilesToMosaic() {

}