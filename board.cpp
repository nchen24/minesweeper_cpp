#include <iostream>
#include "board.h"

Board::Board(){

}

Board::Board(const unsigned sizeHoriz, const unsigned sizeVert, const unsigned numMines, const unsigned seed){
    this->sizeVert  = sizeVert;
    this->sizeHoriz = sizeHoriz;
    boardContents = new bool*[sizeVert];
    boardDisplay  = new char*[sizeVert];
    boardState    = new CELL_STATE*[sizeVert];
    for(unsigned row = 0 ; row < sizeVert ; row++){
        boardContents[row] = new bool[sizeHoriz];
        boardDisplay[row]  = new char[sizeHoriz];
        boardState[row]    = new CELL_STATE[sizeHoriz];
    }

    for(unsigned row = 0 ; row < sizeVert ; row++){
        for(unsigned col = 0 ; col < sizeHoriz ; col++){
            boardContents[row][col] = false;
            boardDisplay[row][col]  = UNOPENED_GFX;
            boardState[row][col]    = CLOSED;
        }
    }
    boardContents[0][0] = true;
}

Board::~Board(){
    for(unsigned row = 0 ; row < sizeVert ; row++){
        delete[] boardContents[row];
        delete[] boardDisplay[row];
        delete[] boardState[row];
    }
    delete[] boardContents;
    delete[] boardDisplay;
    delete[] boardState;
}

bool Board::openCell(const char x, const int y){
    const unsigned row = y;
    const unsigned col = x - 'a';
    validateInput(row, col);
    
    // TODO: Change boardDisplay
    boardDisplay[row][col] = boardContents[row][col] ? MINE_GFX : '0';
    boardState[row][col] = OPEN;

    return boardContents[row][col];
}

void Board::flagCell(const char x, const int y){
    const unsigned row = y;
    const unsigned col = x - 'a';
    validateInput(row, col);

    boardDisplay[row][col] = FLAGGED_GFX;

}

void Board::printBoard(){
    // To leave room for the numbers down the side
    std::cout << (sizeVert > 9 ? "   " : "  "); 
    for(unsigned i = 0 ; i < sizeHoriz ; i++){
        std::cout << (char)('a' + i) << " ";
    }
    std::cout << "\n";

    for(unsigned row = 0 ; row < sizeVert ; row++){
        if(row < 10 && sizeVert > 9){
            std::cout << " ";
        }
        std::cout << row << " ";
        for(unsigned col = 0 ; col < sizeHoriz ; col++){
            std::cout << (boardState[row][col] == OPEN ? boardDisplay[row][col] : '?') << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Board::validateInput(const int row, const int col){
    if(row > sizeVert || col > sizeHoriz){
        std::cerr << "Error: Out of bounds\n";
        //throw OUT_OF_BOUNDS_EXCEPTION;
    }
}
