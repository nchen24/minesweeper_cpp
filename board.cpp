#include <iostream>
#include "board.h"

Board::Board(){

}

Board::Board(const unsigned sizeHoriz, const unsigned sizeVert, const unsigned numMines, const unsigned seed){
    this->sizeVert  = sizeVert;
    this->sizeHoriz = sizeHoriz;
    boardContents = new bool*[sizeVert];
    boardDisplay  = new char*[sizeVert];
    for(unsigned row = 0 ; row < sizeVert ; row++){
        boardContents[row] = new bool[sizeHoriz];
        boardDisplay[row]  = new char[sizeHoriz];
    }

    for(unsigned row = 0 ; row < sizeVert ; row++){
        for(unsigned col = 0 ; col < sizeHoriz ; col++){
            boardDisplay[row][col] = '?';
        }
    }
}

Board::~Board(){
    for(unsigned row = 0 ; row < sizeVert ; row++){
        delete[] boardContents[row];
        delete[] boardDisplay[row];
    }
    delete[] boardContents;
    delete[] boardDisplay;
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
            std::cout << boardDisplay[row][col] << " ";
        }
        std::cout << "\n";
    }
}
