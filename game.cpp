#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include "game.h"
        
Game::Game(){
    this->seed = time(0);
    init();
}

Game::Game(unsigned seed){
    this->seed = seed;
    init();
}

void Game::remake(){
    std::cout << "Remaking...\n";
    delete theBoard;
    seed = rand();
    init();
}

void Game::init(){
    boardCols = 10;
    boardRows = 10;
    numMines  = 15;
    srand(seed);
    theBoard = new Board(boardCols, boardRows, numMines, seed);
    turnNum = 0;
}

int Game::play(){
    bool gameOver = false;
    std::string input = "";
    BoardCoordinates currentPlay;

    while(!gameOver){
        theBoard->printBoard();
        currentPlay = getInput();
        gameOver = theBoard->openCell(currentPlay);
        if(turnNum == 0){
            while(gameOver){
                remake();
                gameOver = theBoard->openCell(currentPlay);
            }
        }
        turnNum++;
    }
    if(gameOver){
        showGameOver();
    }
    return 0;
}

void Game::showGameOver(){
    theBoard->printBoard();
    std::cout << "Game over, you lose!\n";
}

BoardCoordinates Game::getInput(){
    std::string input = "";
    BoardCoordinates currentPlay;

    do{
        std::cin >> input;
    } while(sscanf(input.c_str(), "%c%u", &currentPlay.column, &currentPlay.row) != 2);

    return currentPlay;
}
