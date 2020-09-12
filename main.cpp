#include <iostream>
#include <string>
#include <sstream>

#define TURNS 5

void openMenu();
void getMenuChoice();
void printCredits();
void exitGame();

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
        std::cout << "new game (to do)" << std::endl;
        openMenu();
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