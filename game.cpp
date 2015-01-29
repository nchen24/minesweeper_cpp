#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include "game.h"
        
Game::Game(){
    srand(time(0));
    theBoard = new Board(10, 10, 15, 0);
}

Game::Game(const unsigned seed){
    srand(seed);
    theBoard = new Board(10, 10, 15, 0);
}

int Game::play(){
    bool gameOver = false;
    std::string input = "";
    BoardCoordinates currentPlay;

    while(!gameOver){
        theBoard->printBoard();
        currentPlay = getInput();
        gameOver = theBoard->openCell(currentPlay);
    }
    return 0;
}

BoardCoordinates Game::getInput(){
    std::string input = "";
    BoardCoordinates currentPlay;

    do{
        std::cin >> input;
    } while(sscanf(input.c_str(), "%c%u", &currentPlay.column, &currentPlay.row) != 2);

    return currentPlay;
}
