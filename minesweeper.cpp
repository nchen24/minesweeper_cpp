#include <iostream>
#include "game.h"
#include "board.h"

int main(){
    std::string input;
    char difficulty;
    Game *g = NULL;
    std::cout << "Welcome to minesweeper! Choose your difficulty level:\n"
              << "[B]eginner: 9x9, 10 mines\n"
              << "[I]ntermediate: 16x16, 40 mines\n"
              << "[E]xpert: 16x30, 99 mines\n"
              << "[C]ustom: Pick your size!\n";
    do{
        std::cin >> input;
        if(input.length() == 1)
            difficulty = input[0];
        switch(difficulty){
            case 'B': g = new Game(9, 9, 10); break;
            case 'I': g = new Game(16, 16, 40); break;
            case 'E': g = new Game(16, 30, 99); break;
            case 'C': std::cout << "Custom currently not supported\n"; break;
            default: std::cout << "Invalid option\n";
        }

    }while(!g);

    g->play();

    delete g;
    return 0;
}

