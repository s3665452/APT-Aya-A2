#include "GameEngine.h"
#include "Types.h"
#include <sstream>
#include <fstream>

GameEngine::GameEngine() {
    this->currentTurn = 0;
    this->playerA = nullptr;
    this->playerB = nullptr;
    this->tileBag = new TileBag();
    this->factories = new Factories(tileBag);
}

GameEngine::~GameEngine() {
    delete playerA;
    delete playerB;
    delete tileBag;
    delete factories;
}

void GameEngine::loadGame(std::string filename){
    if(filename.size() > 0){
       filename += ".save";
       filename = "save/"+filename;
       std::string file;
       std::ifstream input (filename);
       bool readGame = false;
       bool readPlayerMosaic = false;
       bool readFactories = false;
       //Factories* factories = nullptr;
       Player* player = nullptr;

    //Player* mosaic[2];
    for(int x = 0; x < 2; x++) {
      //      mosaic[x] = nullptr;
        }
        if(input.is_open()) {
            while(getline(input,file)) {
            if(file == "game") readGame = true;
            else if(file == "mosaic") readPlayerMosaic = true;
            else if(file == "factories") readFactories = true;

            if(readGame == true) {
                std::string typefile;
                std::string inputfile;
            for(int x =0; x < (int) file.length(); x++) {
                if(file[x] != ' ') {
                  inputfile.push_back(file[x]);
                } else {
                  typefile = inputfile;
                  inputfile = " ";
                        } if (x == (int)file.length()-1) {
                             if(typefile == "play"){
                                 if(currentPlayer != nullptr && currentPlayer->getName()==inputfile){
                                    player->printInfo();
                                } else if(typefile == "round") {
                                    factories->getFactory(FACTORYNUMBER);
                                    this->newGame(false);
                                }
                            } if (typefile == " "){
                                readGame = false;    
                            }else if(readPlayerMosaic == true){
                                std::string typefile;
                                std::string inputfile;
                                for(int x =0; x <(int) file.length(); x++) {
                                    if(file[x] != ' '){
                                        inputfile.push_back(file[x]);
                                    } else if (file[x] == ' ') {
                                        typefile = inputfile;
                                        inputfile = " ";
                                    } if(x == (int)file.length()-1) {
                                      if(typefile == "gameName"){
                                        player = new Player(inputfile);
                                    } else if(typefile == "score") {
                                        player->getScore();
                                    } else if(typefile == "brokenPts") {
                                        int emptyBrokenPts = 0;
                                        if(inputfile != "E"){
                                            for(int i = 0; i < (int)inputfile.length(); i++){
                                                    player->emptyBroken(tileBag);
                                                    if(inputfile[i] == 'F'){
                                                        //player->tileTheWall;
                                                    }
                                                    emptyBrokenPts++;
                                                }
                                        if(inputfile == " ") {
                                           for(int x = 0; x < 2; x++){
                                               if(currentPlayer == nullptr){
                                                    currentPlayer = player;
                                                    x = 2;
                                               }
                                           }
                                           readPlayerMosaic = false;
                                        }
                                      }
                                    } else if(readFactories == true){
                                        std::string typefile;
                                        std::string inputfile;
                                        for(int x =0; x <(int) inputfile.length(); x++){
                                            if(inputfile[x] != ' '){
                                               inputfile.push_back(inputfile[x]);  
                                            } else if(inputfile[x] == ' '){
                                              typefile = inputfile;
                                              inputfile = " ";
                                            } if(x ==(int) inputfile.length()-1) {
                                              if(typefile == "factories") {
                                                factories->getFactory(FACTORYNUMBER);
                                                //int currLine = 0;
                                                //int currCol = 0;
                                              }
                                            }
                                          }
                                        }          
                                      }
                                    }
                                  }
                        }
                    }
                }
            }
       input.close();
      } else {
        //if the file cannot be found
        std::cout << "File cannot be found" <<std::endl;
      }
    } else {   
        std::cout << "Error: Please enter a valid filename!"<<std::endl;
    }
}
void GameEngine::saveGame() {

}

void GameEngine::newGame(bool startgame) {
    std::string playerNameA;
    std::string playerNameB;

    //Testing
    //this->tileBag->printAll();

    //bool loadGame = false;
    // start a new game
    if (startgame == true) {
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


        // >>>play two rounds <<<
        while(currentTurn < 2) {
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
        for(int n = i ; n >= 0; n--) {
            std::cout << " " << player->store[i][n];  
        }
        std::cout << " ||";
        // Print board row
        for(int n = 0; n < MOSAIC_DIM; n++) {
            std::cout << " " << player->board[i][n].second;
        }
        // Print underlaying colours (test)
        for(int n = 0; n < MOSAIC_DIM; n++) {
            std::cout << " " << player->board[i][n].first;
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
 
    if(turn != "turn" || factoryNum < 0 || factoryNum > 5 || !isTile(tile) || storeNum < 1 || storeNum > 5 || !contains(factories->getFactory(factoryNum), tile) || currentPlayer->isFull(storeNum) || (currentPlayer->storeColour(storeNum) != tile && currentPlayer->storeColour(storeNum) != '.') || currentPlayer->tileCovered(storeNum, tile)) {
        if(storeNum != 6 || !contains(factories->getFactory(factoryNum), tile)) {
            std::cout << "Invalid Input" << std::endl;
            getCommand();
        }
    }

    selectTile(factoryNum, tile, storeNum);
    std::cout << "Turn successful." << std::endl;
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
    while(currentPlayer->broken[i] != 'F') {
        if(i < currentPlayer->broken.size()) {
            i += 1;
        }
        else {
            changePlayer();
            i = 0;
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