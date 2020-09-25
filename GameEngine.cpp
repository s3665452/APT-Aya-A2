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

        //Test
        // printFactories();
        // printMosaic(*playerA);
        // printFactories();
        // printMosaic(*playerB);

        //while(!endTurn(factories, this->numFac)) {
        //for(int x = 0; x < this->numFac; ++x){
        //The turn run until the factories is empty
        playerA->isTheTurn();
        std::cout<<"TURN FOR PLAYER: "<< playerA->getName()<<"   ";
        std::cout<<"SCORE: "<<playerA->getScore() << std::endl;
        printFactories();
        std::cout << std::endl;
        printMosaic(*playerA);
        std::cout<<std::endl;
                   
        playerB->isTheTurn();
        std::cout<<"TURN FOR PLAYER: "<< playerB->getName()<<"   ";
        std::cout<<"SCORE: "<<playerB->getScore() << std::endl;
        printFactories();
        std::cout << std::endl;
        printMosaic(*playerB);
        std::cout<<std::endl;


        factories->~Factories();
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

bool GameEngine::endTurn(Factories* factories, int num){
        //check the factories are empty to end a turn
        if(factories->isEmpty()) {
            return true;
        }
    return false;
}

void GameEngine::printFactories() {
    std::cout << "Factories:" << std::endl;
    for(int i = 0; i < FACTORYNUMBER; i++) {
        std::cout << i << ":";
        for(long unsigned int n = 0; n < factories->getFactory(i).size(); n++) {
            std::cout << " " << factories->getFactory(i)[n];
        }
        std::cout << std::endl;
    }
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