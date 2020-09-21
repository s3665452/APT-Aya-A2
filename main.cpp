#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include "Types.h"
#include "Player.h"
#include "TileBag.h"
#include "GameEngine.h"

#define TURNS 5

void openMenu();
void getMenuChoice();
void printCredits();
void exitGame();
void newGame();

int main(void){

    std::cout << "Welcome to Azul!" << std::endl << "-------------------" << std::endl;
    openMenu();

    return EXIT_SUCCESS;
}

void openMenu(){
    std::cout << std::endl << "Menu" << std::endl << "----" << std::endl << "1. New Game" << std::endl
    << "2. Load Game" << std::endl << "3. Credits" << std::endl << "4. Quit" << std::endl << std::endl;
    getMenuChoice();
}

void printCredits(){
    std::cout << std::endl << "----------------------------------" << std::endl << "Name: Adabel Choi" << std::endl
    << "Student ID: S3758949" << std::endl << "Email: S3758949@student.rmit.edu.au" << std::endl << "Name: Andong Wang" << std::endl
    << "Student ID: S3665452" << std::endl << "Email: S3665452@student.rmit.edu.au" << std::endl << "Name: Yadursha Vakeesan" << std::endl
    << "Student ID: S3748401" << std::endl << "Email: S3748401@student.rmit.edu.au" << std::endl << "----------------------------------" << std::endl;
}

void exitGame(){

    std::cout << std::endl << "Goodbye" << std::endl;
    exit(EXIT_SUCCESS);
}

void getMenuChoice(){
    int choice = 0;
    std::cout << "> ";

    std::string line;
    getline( std::cin, line );
    std::istringstream is(line);
   
    is >> choice;

    if(std::cin.eof()){
        exitGame();
    }

    if(choice == 1){
        GameEngine* gameEngine = new GameEngine();
        gameEngine->newGame();
    }
    else if(choice == 2){
        std::cout << "load game (to do)" << std::endl;
        openMenu();
    }
    else if(choice == 3){
        printCredits();
        openMenu();
    }
    else if(choice == 4){
        exitGame();
    }
    else {
        std::cout << "Invalid Input" << std::endl;
        getMenuChoice();
    }
}

// void newGame(){
//     std::string playerNameA;
//     std::string playerNameB;
//     TileBag* tileBag = new TileBag();
//    //Testing
//    tileBag->printAll();

//     std::cout << std::endl;

//     std::cout << "Starting a New Game" << std::endl << std::endl;
//     std::cout << "Enter a name for player 1" << std::endl << "> ";
//     std::cin >> playerNameA;
//     std::cout << std::endl << "Enter a name for player 2" << std::endl << "> ";
//     std::cin >> playerNameB;

//     Player* playerA = new Player(playerNameA);
//     Player* playerB = new Player(playerNameB);
//     std::cout << std::endl << "Let's Play!" << std::endl;

//     std::cout << playerA->getName() << std::endl;
//     std::cout << playerB->getName() << std::endl;
 
// }
