#include "GameEngine.h"
#include "Types.h"
#include <sstream>
#include <fstream>
#include <cstring>

GameEngine::GameEngine() {
    // Initialise variables
    this->currentTurn = 0;
    this->playerA = nullptr;
    this->playerB = nullptr;
    this->tileBag = nullptr;
    this->factories = nullptr;
    this->testingMode = false;
    this->loadFileName = " ";
}

GameEngine::~GameEngine() {
    cleanUp();
}

void GameEngine::loadGame() {
    // If file name does not exist, get user input from stdin
    if(loadFileName == " ") {
        std::cout << "> ";
        std::cin >> loadFileName;

        if(std::cin.eof()){
            exitGame();
        }
    }
    // Create the ifstream using the file name
    std::ifstream infile(loadFileName);

    std::string line;
    int lineNum = 0;
    // Keep reading lines until the end of file or reach maximum number of rounds
    while (std::getline(infile, line) && currentTurn < MAX_ROUNDS) {
        if(lineNum == 0) {
            // If the length of first line is not equal tile bag size, its not a valid file
            if(line.size() != TILEBAG_SIZE) {
                std::cout << "Invalid File" << std::endl;
                // If not in testing mode, ask the user to input a new file name, otherwise exit
                if(testingMode == false) {
                    loadFileName = " ";
                    loadGame();
                }
                else {
                    exitGame();
                }
            }
            else {
                // Create the tile bag and factories, save the line
                const char* ORDER = line.c_str();
                this->tileBag = new TileBag(ORDER);
                this->factories = new Factories(tileBag);
                saved.add_back(line);
            }
        }
        // If it's the second line (username of the first user), create a user, save the line
        else if (lineNum == 1) {
            this->playerA = new Player(line);
            saved.add_back(line);
        }
        // If it's the third line (username of the second user), create a user, save the line
        else if (lineNum == 2) {
            this->playerB = new Player(line);
            saved.add_back(line);
        }
        else {
            // create a istringstream using the line, get values
            std::istringstream is(line);

            std::string turn;
            int factoryNum;
            char tile;
            int storeNum;

            is >> turn;
            is >> factoryNum;
            is >> tile;
            is >> storeNum;
            // If it's the forth line, set current player to be the first player
            if(lineNum == 3) {
                currentPlayer = playerA;
            }
            // Validite input, only move tiles if the input satisfies
            // 1. The first word is "turn"
            // 2. Factory num is from 0 to 5
            // 3. The third word is a valid tile
            // 4. Store num is from 1 to 5
            // 5. The selected factory contains tile of the selected colour
            // 6. The selected store row of the player is not full
            // 7. The selected store row of the player is empty or contains selected colour of tile
            // 8. The position on the row of the player mosaic is not covered with tile of selected colour
            // Or
            // 1. Selected store number is 6 (broken)
            // 2. The selected factory contains tile of the selected colour
            // In this case selected tiles will be moved directly to the broken row
            // If does not satisfy, the program will report invaild input and exit
            if((turn != "turn" || factoryNum < 0 || factoryNum > 5 || !isTile(tile) || storeNum < 1 || storeNum > 5 || !contains(factories->getFactory(factoryNum), tile) || currentPlayer->isFull(storeNum) || (currentPlayer->storeColour(storeNum) != tile && currentPlayer->storeColour(storeNum) != '.') || currentPlayer->tileCovered(storeNum, tile)) && (storeNum != 6 || !contains(factories->getFactory(factoryNum), tile))) {
                if(line.size() > 1) {
                std::cout << "Invalid Input At Line " << lineNum + 1 << std::endl;
                std::cout << "Line: " << line << std::endl;
                exitGame();
                }
            }
            else {
                // Move tiles and save the line
                selectTile(factoryNum, tile, storeNum);
                saved.add_back(line);
                // If factories is empty, tile the wall for players and refill factories, set the player who has 'F' as current player, go to next round
                if(factories->isEmpty()) {
                setFirstPlayer();
                playerA->tileTheWall(tileBag);
                playerB->tileTheWall(tileBag);
                factories->fillFactories(tileBag);
                currentTurn += 1;
                }
                // If not empty, change player
                else {
                    changePlayer();
                }
            }
        }
        lineNum += 1;
    }
    // If there are less than 3 lines in the file, reload if not in testing mode, otherwise exit
    if(lineNum < 3) {
        std::cout << "Invalid File" << std::endl;
        if(testingMode == false) {
            loadFileName = " ";
            loadGame();
        } else {
            exitGame();
        }
    }
    // If not in testing mode, continue game play until reach max number of rounds
    if(this->testingMode == false) {
        std::cout << "Azul game successfully loaded" << std::endl << std::endl;
        if(currentTurn < MAX_ROUNDS) {
            std::string dummy;
            getline(std::cin, dummy);
            // Player until the end of the round
            while(!factories->isEmpty())
            {
                //The turn run until the factories is empty
                std::cout<<"TURN FOR PLAYER: "<< currentPlayer->getName() << std::endl;
                printFactories();
                printMosaic(currentPlayer);
                getCommand();
                changePlayer();
            }
            setFirstPlayer();
            playerA->tileTheWall(tileBag);
            playerB->tileTheWall(tileBag);
            std::cout << playerA->getName() << " Score: " << playerA->getScore() << std::endl;
            std::cout << playerB->getName() << " Score: " << playerB->getScore() << std::endl;
            std::cout << "=== End Of Round " << currentTurn + 1 << " ===" << std::endl;
            factories->fillFactories(tileBag);
            currentTurn += 1;
        }
        // Keep playing until reaching max number of rounds
        while(currentTurn < MAX_ROUNDS) {
            playOneRound();
            factories->fillFactories(tileBag);
            currentTurn += 1;
        }
        printResult();
    }
    // If in testing mode, print factories and players' mosaics
    else {
        if(factories->isEmpty()) {
            setFirstPlayer();
            playerA->tileTheWall(tileBag);
            playerB->tileTheWall(tileBag);
            factories->fillFactories(tileBag);
            currentTurn += 1;
        }
        printFactories();
        std::cout << "Score for Player " << playerA->getName() << ": " << playerA->getScore() << std::endl;
        printMosaic(playerA);
        std::cout << "Score for Player " << playerB->getName() << ": " << playerB->getScore() << std::endl;
        printMosaic(playerB);
    }
    // Clean up memory
    cleanUp();
}
    
// Output everything stored to a file
void GameEngine::saveGame(std::string filename) {
    std::ofstream out(filename);
    for(int i = 0; i < saved.size(); i++) {
        out << saved.get(i) << std::endl;
    }
    out << std::endl;
    out.close();
    std::cout << "Game successfully saved to " << filename << std::endl;
}


void GameEngine::newGame() {
    std::string playerNameA;
    std::string playerNameB;
    // Create tile bag using default tile order, create factories
    tileBag = new TileBag(TILEBAG_ORDER);
    factories = new Factories(tileBag);
    saved.add_back(TILEBAG_ORDER);

    // start a new game, get player names from stdin
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
    // Set current player to player A
    this->currentPlayer = playerA;

    // Player until reaching max number of rounds
    while(currentTurn < MAX_ROUNDS) {
        playOneRound();
        factories->fillFactories(tileBag);
        currentTurn += 1;
    }
    printResult();
    // Clean up memories 
    cleanUp();
}


void GameEngine::playOneRound(){
    std::cout << std::endl;
    std::cout << "=== Start Round " << currentTurn + 1 << " ===";
    std::cout << std::endl;
    while(!factories->isEmpty()) {
        //The turn run until the factories is empty
        std::cout<<"TURN FOR PLAYER: "<<currentPlayer->getName() << std::endl;
        printFactories();
        printMosaic(currentPlayer);
        getCommand();
        changePlayer();
    }
    // Set the player with 'F' to be current player, tile the wall and score points
    setFirstPlayer();
    playerA->tileTheWall(tileBag);
    playerB->tileTheWall(tileBag);
    // Print player score at the end of the round
    std::cout << playerA->getName() << " Score: " << playerA->getScore() << std::endl;
    std::cout << playerB->getName() << " Score: " << playerB->getScore() << std::endl;
    std::cout << "=== End Of Round " << currentTurn + 1 << " ===" << std::endl;
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
          if(currentPlayer->broken.size() < BROKEN_MAX_SIZE) {
                currentPlayer->broken.push_back('F');
            }
            selectedFactory->erase(selectedFactory->begin() + i);
        }
        // If it is selected tile, put it to player store or broken
        else if ((*selectedFactory)[i] == tile) {
            if(storeNum != 6) {
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
             if(factoryNum == 0) {
                i += 1;
             }
             else {
                 factories->getFactory(0)->push_back((*selectedFactory)[i]);
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
        getCommand();
    } 
    else {
        is >> factoryNum;
        is >> tile;
        is >> storeNum;
        // If eof detected, clean up memories and exit
        if(std::cin.eof()){
            cleanUp();
            exitGame();
        }
        // Varify inputs, if not satisfied, ask the user to input again
        if((turn != "turn" || factoryNum < 0 || factoryNum > 5 || !isTile(tile) || 
            storeNum < 1 || storeNum > 5 || !contains(factories->getFactory(factoryNum), tile) || 
            currentPlayer->isFull(storeNum) || (currentPlayer->storeColour(storeNum) != tile && 
            currentPlayer->storeColour(storeNum) != '.') || currentPlayer->tileCovered(storeNum, tile)) && 
            (storeNum != 6 || !contains(factories->getFactory(factoryNum), tile))) {
            std::cout << "Invalid Input" << std::endl;
            getCommand();
        }
        else {
            selectTile(factoryNum, tile, storeNum);
            saved.add_back(line);
            std::cout << "Turn successful." << std::endl << std::endl;
        }
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
    bool containF = false;
    while(i < currentPlayer->broken.size()) {
        if(currentPlayer->broken[i] == 'F') {
            containF = true;
        }
        i += 1;
    }
    if(containF == false) {
        changePlayer();
    }
}

// End game result
void GameEngine::printResult() {
    std::cout<<std::endl;
    std::cout<<"=== GAME OVER ===";
    std::cout<<std::endl;        
    // Compare scores to decide the winner of the game
    std::cout << std::endl;
    std::cout << "Final Scores: " << std::endl;
    std::cout << playerA->getName()<< ": " << playerA->getScore() << std::endl; 
    std::cout << playerB->getName()<< ": " << playerB->getScore() << std::endl; 

    if(playerA->getScore() == playerB->getScore()) {
        std::cout << "Draw!" << std::endl;
    } else if(playerA->getScore() > playerB->getScore()) {
        std::cout << "Player " << playerA->getName() <<" wins!"<< std::endl;
    } else {
        std::cout << "Player " << playerB->getName() <<" wins!"<< std::endl;
    }                                     
}


void GameEngine::cleanUp() {
    delete playerA;
    delete playerB;
    delete tileBag;
    delete factories;
}