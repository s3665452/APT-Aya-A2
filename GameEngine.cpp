#include "GameEngine.h"
#include "Types.h"
#include <sstream>
#include <fstream>
#include <cstring>

GameEngine::GameEngine() {
    this->currentTurn = 0;
    this->playerA = nullptr;
    this->playerB = nullptr;
    this->tileBag = nullptr;
    this->factories = nullptr;
    this->testingMode = false;
    this->loadFileName = " ";
}

GameEngine::~GameEngine() {
    delete playerA;
    delete playerB;
    delete tileBag;
    delete factories;
}

void GameEngine::loadGame() {
    if(loadFileName == " ") {
        std::cout << "> ";
        std::cin >> loadFileName;

        if(std::cin.eof()){
            exitGame();
        }
    }

    std::ifstream infile(loadFileName);

    std::string line;
    int lineNum = 0;

    while (std::getline(infile, line)) {
       // std::cout << line << line.size() << std::endl;
        if(lineNum == 0) {
            if(line.size() != 100) {
                std::cout << "Invalid File" << std::endl;
                if(testingMode == false) {
                    loadFileName = " ";
                    loadGame();
                }
                else {
                    exitGame();
                }
            }
            else {
                const char* ORDER = line.c_str();
                this->tileBag = new TileBag(ORDER);
                this->factories = new Factories(tileBag);
                saved.add_back(line);
            }
        }
        else if (lineNum == 1) {
            this->playerA = new Player(line);
            saved.add_back(line);
        }
        else if (lineNum == 2) {
            this->playerB = new Player(line);
            saved.add_back(line);
        }
        else {
            std::istringstream is(line);

            std::string turn;
            int factoryNum;
            char tile;
            int storeNum;

            is >> turn;
            is >> factoryNum;
            is >> tile;
            is >> storeNum;


            if(factories->isEmpty()) {
                setFirstPlayer();
                playerA->tileTheWall(tileBag);
                playerB->tileTheWall(tileBag);
                factories->fillFactories(tileBag);
                currentTurn += 1;
            }
            else {
                if(lineNum == 3) {
                    currentPlayer = playerA;
                }
                else {
                    changePlayer();
                }
            }

            if((turn != "turn" || factoryNum < 0 || factoryNum > 5 || !isTile(tile) || storeNum < 1 || storeNum > 5 || !contains(factories->getFactory(factoryNum), tile) || currentPlayer->isFull(storeNum) || (currentPlayer->storeColour(storeNum) != tile && currentPlayer->storeColour(storeNum) != '.') || currentPlayer->tileCovered(storeNum, tile)) && (storeNum != 6 || !contains(factories->getFactory(factoryNum), tile))) {
                //std::string newLine = "\n";
                if(line.size() > 1) {
                std::cout << "Invalid Input At Line " << lineNum + 1 << std::endl;
                exitGame();
                }
            }
            else {
                selectTile(factoryNum, tile, storeNum);
                saved.add_back(line);
           }
        }
        lineNum += 1;
    }
    // If there are less than 3 lines in the file, reload
    if(lineNum < 3) {
        std::cout << "Invalid Fil" << std::endl;
        if(testingMode == false) {
            loadFileName = " ";
            loadGame();
        } else {
            exitGame();
        }
    }

    if(this->testingMode == false) {
        std::cout << "Azul game successfully loaded" << std::endl << std::endl;
        std::string dummy;
        getline(std::cin, dummy);
        while(!factories->isEmpty())
        {
            //The turn run until the factories is empty
            std::cout<<"TURN FOR PLAYER: "<<currentPlayer->getName() << std::endl;
            printFactories();
            printMosaic(currentPlayer);
            getCommand();
            changePlayer();
        }

        printMosaic(playerA);
        printMosaic(playerB);
        setFirstPlayer();
        std::cout << "First player set " << currentPlayer->getName() << std::endl;
        playerA->tileTheWall(tileBag);
        std::cout << "PlayerA tile" << std::endl;
        playerB->tileTheWall(tileBag);
        std::cout << "PlayerB tile" << std::endl;

        factories->fillFactories(tileBag);
        currentTurn += 1;

        while(currentTurn < TURNS) {
            playOneRound();
            factories->fillFactories(tileBag);
            currentTurn += 1;
        }
        printResult();
    }
    else {
        printFactories();
        std::cout << "Score for Player " << playerA->getName() << ": " << playerA->getScore() << std::endl;
        printMosaic(playerA);
        std::cout << "Score for Player " << playerB->getName() << ": " << playerB->getScore() << std::endl;
        printMosaic(playerB);
    }
}
    

void GameEngine::saveGame(std::string filename) {
    std::ofstream out(filename);
    while(saved.size() != 0) {
        std::cout << saved.getFront() << saved.size() << std::endl;
        out << saved.getFront() << std::endl;
        saved.removeFront();
    }
    out.close();
    std::cout << "Game saved successfully" << std::endl;
}


void GameEngine::newGame() {
    std::string playerNameA;
    std::string playerNameB;

    tileBag = new TileBag(TILEBAG_ORDER);
    factories = new Factories(tileBag);
    saved.add_back(TILEBAG_ORDER);

    // start a new game
    std::cout << "Starting a New Game" << std::endl << std::endl;
    std::cout << "Enter a name for player 1" << std::endl << "> ";
    std::cin >> playerNameA;
    std::cout << std::endl << "Enter a name for player 2" << std::endl << "> ";
    std::cin >> playerNameB;
    std::string dummy;
    getline(std::cin, dummy);
    this->playerA = new Player(playerNameA);
    this->playerB = new Player(playerNameB);
    saved.add_back(playerNameA);
    saved.add_back(playerNameB);
    std::cout << std::endl << "Let's Play!" << std::endl;

    std::cout << playerA->getName() << std::endl;
    std::cout << playerB->getName() << std::endl;

    std::cout << std::endl;
    std::cout << "=== Start Round ===";
    std::cout << std::endl;

    this->currentPlayer = playerA;

    // >>>play 5 rounds <<<
    while(currentTurn < TURNS) {
        playOneRound();
        factories->fillFactories(tileBag);
        currentTurn += 1;
    }
    printResult();
}

void GameEngine::playOneRound(){
    while(!factories->isEmpty()) {
        //The turn run until the factories is empty
        std::cout<<"TURN FOR PLAYER: "<<currentPlayer->getName() << std::endl;
        printFactories();
        printMosaic(currentPlayer);
        getCommand();
        changePlayer();
    }
    printMosaic(playerA);
    printMosaic(playerB);
    setFirstPlayer();
    std::cout << "First player set " << currentPlayer->getName() << std::endl;
    playerA->tileTheWall(tileBag);
    std::cout << "PlayerA tile" << std::endl;
    playerB->tileTheWall(tileBag);
    std::cout << "PlayerB tile" << std::endl;
    

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
    std::cout << std::endl;
}

// Print mosaic for a player
void GameEngine::printMosaic(Player* player) const {
    std::cout << "Mosaic for " << player->getName() << ":" << std::endl;
    for(int i = 0; i < MOSAIC_DIM; i++) {
        // Print row number
        std::cout << i + 1 << ":";
        // Print white space before mosaic row
        for(int n = MOSAIC_DIM - i - 1; n > 0; n--) {
            std::cout << "  ";
        }
        // Print store row
        for(int n = i ; n >= 0; n--) {
            std::cout << " " << player->store[i][n];  
        }
        std::cout << " ||";
        // Print board row
        for(int n = 0; n < MOSAIC_DIM; n++) {
            std::cout << " " << player->board[i][n].second;
        }
        // Print underlaying colours (test)
        // for(int n = 0; n < MOSAIC_DIM; n++) {
        //     std::cout << " " << player->board[i][n].first;
        // }
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

// Select tiles to put in store, if storeNum = 6, move tiles to the broken directly
void GameEngine::selectTile(int factoryNum, char tile, int storeNum) {
    std::vector<char>* selectedFactory = factories->getFactory(factoryNum);
   
    long unsigned int i = 0;
    while( i < selectedFactory->size()) {
        // Put F to broken directly
        if((*selectedFactory)[i] == 'F') {
          //  std::cout << "Tile: " << "F" << std::endl;
          if(currentPlayer->broken.size() < BROKEN_MAX_SIZE) {
                currentPlayer->broken.push_back('F');
            }
            selectedFactory->erase(selectedFactory->begin() + i);
        }
        // If it is selected tile, put it to player store or broken
        else if ((*selectedFactory)[i] == tile) {
            if(storeNum != 6) {
                //   std::cout << "Tile: " << tile << std::endl;
                // Iterate until find empty or reach the maximum size
                int n = 0;
                while(currentPlayer->store[storeNum-1][n] != '.' && n < storeNum) {
                    n += 1;
                }
                // If there is a empty spot, put the tile in, otherwise put the tile to broken
                if(n < storeNum) {
                    currentPlayer->store[storeNum-1][n] = tile;
                }
                else {
                    if(currentPlayer->broken.size() < BROKEN_MAX_SIZE) {
                        currentPlayer->broken.push_back(tile);
                    }
                    else {
                        tileBag->enqueue(tile);
                    }
                }  
            }
            else {
                if(currentPlayer->broken.size() < BROKEN_MAX_SIZE) {
                        currentPlayer->broken.push_back(tile);
                    }
                else {
                        tileBag->enqueue(tile);
                    }
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

// Get a line of input from user, varify and execute
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
    // Save and exit when user input save
    if(turn == "save") {
        std::string fileName;
        is >> fileName;
        saveGame(fileName);
        exitGame();
    }
    is >> factoryNum;
    is >> tile;
    is >> storeNum;

    if(std::cin.eof()){
        exitGame();
    }

    // std::cout << turn << std::endl;
    // std::cout << factoryNum << std::endl;
    // std::cout << tile << std::endl;
    // std::cout << storeNum << std::endl;
 
    if((turn != "turn" || factoryNum < 0 || factoryNum > 5 || !isTile(tile) || storeNum < 1 || storeNum > 5 || !contains(factories->getFactory(factoryNum), tile) || currentPlayer->isFull(storeNum) || (currentPlayer->storeColour(storeNum) != tile && currentPlayer->storeColour(storeNum) != '.') || currentPlayer->tileCovered(storeNum, tile)) && (storeNum != 6 || !contains(factories->getFactory(factoryNum), tile))) {
        std::cout << "Invalid Input" << std::endl;
        getCommand();
    }
    else {
        selectTile(factoryNum, tile, storeNum);
        saved.add_back(line);
        std::cout << "Turn successful." << std::endl;
    }


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

// Set the player who has 'F' to current player
void GameEngine::setFirstPlayer() {
    long unsigned int i = 0;
    bool changed = false;
    while(currentPlayer->broken[i] != 'F' && changed == false) {
        if(i < currentPlayer->broken.size()) {
            i += 1;
        }
        else {
            changePlayer();
            // When no one has F (extremly rare), make sure to change player only once
            changed = true;
        }
    }
}

// End game result
void GameEngine::printResult() {

    // Test
    printMosaic(playerA);
    printMosaic(playerB);
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
    delete factories;
}