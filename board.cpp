#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include "board.h"

Board::Board(){

}

Board::Board(const unsigned sizeHoriz, const unsigned sizeVert, const unsigned numMines, const unsigned seed){
    this->sizeVert   = sizeVert;
    this->sizeHoriz  = sizeHoriz;
    this->startMines = numMines;
    this->remMines   = this->startMines;
    std::srand(seed);

    theBoard = new Cell*[sizeVert];
    for(unsigned row = 0 ; row < sizeVert ; row++){
        theBoard[row] = new Cell[sizeHoriz];
    }
    // TODO: Generate random mines

    for(unsigned row = 0 ; row < sizeVert ; row++){
        for(unsigned col = 0 ; col < sizeHoriz ; col++){
            // Set cell based on whether a mine or not
            theBoard[row][col].setMine(false);
            theBoard[row][col].setNeighbors(0);
        }
    }
    makeRandomBoard(); 
    std::cout << "Made board " << this->sizeVert << "x" << this->sizeHoriz << "\n";
}

Board::~Board(){
    for(unsigned row = 0 ; row < sizeVert ; row++){
        delete[] theBoard[row];
    }
    delete[] theBoard;
}

bool Board::openCell(BoardCoordinates play){
    // Returns true if the player blew up, else returns false.
    unsigned row = play.row;
    unsigned col = play.column - (unsigned)'a';
    validateInput(row, col);
    //if(!validateInput(row, col))
    //    return false;
    
    if(!theBoard[row][col].canBeOpened())
        return false;

    theBoard[row][col].open();

    return theBoard[row][col].isMine();
}

void Board::flagCell(const char x, const int y){
    const unsigned row = y;
    const unsigned col = x - 'a';
    validateInput(row, col);

    theBoard[row][col].flag(); 
}

void Board::printBoard(){
    // To leave room for the numbers down the side
    std::cout << (sizeVert > 9 ? "   " : "  "); 
    for(unsigned i = 0 ; i < sizeHoriz ; i++){
        std::cout << (char)('a' + i) << " ";
    }
    std::cout << "\n";

    for(unsigned row = 0 ; row < sizeVert ; row++){
        // Print the numbers down the side
        if(row < 10 && sizeVert > 9){
            std::cout << " ";
        }
        std::cout << row << " ";
        
        // Print the actual board
        for(unsigned col = 0 ; col < sizeHoriz ; col++){
            std::cout << theBoard[row][col].getDisplay() << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Board::validateInput(const unsigned row, const unsigned col){
    if(row > sizeVert || col > sizeHoriz){
        std::cerr << "Error: Out of bounds\n";
        //throw OUT_OF_BOUNDS_EXCEPTION;
    }
}

int RNG(int i){ return rand() % i; } // TODO: Check if this is truly random

void Board::makeRandomBoard(){
    unsigned boardSize = sizeVert * sizeHoriz;
    std::vector<unsigned> mineLocations(boardSize);
    for(unsigned i = 0; i < boardSize ; i++){
        mineLocations[i] = i;
    }
    std::random_shuffle(mineLocations.begin(), mineLocations.end(), RNG);
    mineLocations.resize(startMines);
    std::sort(mineLocations.begin(), mineLocations.end());
    for(unsigned i = 0 ; i < mineLocations.size() ; i++)
        std::cout << mineLocations[i] << " ";
    std::cout << "\n";

    for(unsigned i = 0 ; i < mineLocations.size() ; i++){
        unsigned row = mineLocations[i] / sizeHoriz;
        unsigned col = mineLocations[i] % sizeHoriz;
        theBoard[row][col].setMine(true);
    }
}
