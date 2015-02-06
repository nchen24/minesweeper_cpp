#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <stdexcept>
#include "game.h"
        
Game::Game(){
    this->seed      = time(0);
    this->boardCols = 10;
    this->boardRows = 10;
    this->numMines  = 15;
    init();
}

Game::Game(unsigned seed){
    this->seed      = seed;
    this->boardCols = 10;
    this->boardRows = 10;
    this->numMines  = 15;
    init();
}
Game::Game(unsigned sizeH, unsigned sizeV, unsigned mines){
    this->seed      = time(0);
    this->boardCols = sizeH;
    this->boardRows = sizeV;
    this->numMines  = mines;
    init();
}
Game::Game(unsigned sizeH, unsigned sizeV, unsigned mines, unsigned seed){
    this->seed      = seed;
    this->boardCols = sizeH;
    this->boardRows = sizeV;
    this->numMines  = mines;
    init();
}

void Game::remake(){
    std::cout << "Remaking...\n";
    delete theBoard;
    seed = rand();
    init();
}

void Game::init(){
    srand(seed);
    theBoard = new Board(boardCols, boardRows, numMines, seed);
    turnNum = 0;
}

int Game::play(){
    bool gameOver = false;
    std::string input = "";
    BoardCoordinates currentPlay;
    BOARD_ACTION action;

    while(!gameOver){
        theBoard->printBoard();
        currentPlay = getInput();
        action = getActionInput();
        try{
            if(action == A_OPEN){
                gameOver = theBoard->openCell(currentPlay);
                
                if(turnNum == 0){
                    while(gameOver){
                        remake();
                        gameOver = theBoard->openCell(currentPlay);
                    }
                }
            } else {
                theBoard->flagCell(currentPlay);
            }
        } catch(const std::out_of_range& e){

        }
        turnNum++;
        if(theBoard->countUnopened() == numMines){
            showWin();
            break;
        }
    }
    if(gameOver){
        showGameOver();
    }
    return 0;
}

void Game::showGameOver(){
    theBoard->showWholeBoard();
    theBoard->printBoard();
    std::cout << "Game over, you lose!\n";
}

void Game::showWin(){
    theBoard->showWholeBoard();
    theBoard->printBoard();
    std::cout << "Congratulations, you win!\n";
}

BoardCoordinates Game::getInput(){
    std::string input = "";
    BoardCoordinates currentPlay;

    do{
        std::cin >> input;
    } while(sscanf(input.c_str(), "%c%u", &currentPlay.column, &currentPlay.row) != 2);

    return currentPlay;
}

BOARD_ACTION Game::getActionInput(){
    std::string input = "";
    do{
        std::cin >> input;
    } while(input != "o" && input != "x");

    return input == "o" ? A_OPEN : A_FLAG;
}
