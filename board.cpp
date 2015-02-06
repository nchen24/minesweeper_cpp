#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
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
    makeBoard();
    setNeighbors();
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
    std::stack<BoardCoordinates> cellsToOpen;

    unsigned row = play.row;
    unsigned col = play.column - (unsigned)'a';
    validateInput(row, col); //TODO: Reimplement this somewhere?

    if(theBoard[row][col].isMine()){
        theBoard[row][col].open();
        return true;
    }

    cellsToOpen.push(play);

    while(!cellsToOpen.empty()){
        BoardCoordinates curCell = cellsToOpen.top();
        cellsToOpen.pop();
        row = curCell.row;
        col = curCell.column - (unsigned)'a';
        if(!theBoard[row][col].isOpen()){
            theBoard[row][col].open();
            if(theBoard[row][col].getDisplay() == EMPTY_GFX){
                // Add neighbors
                addNeighbors(row, col, cellsToOpen);
            }
        }
    }
    return false;
}

void Board::addNeighbors(int row, int col, std::stack<BoardCoordinates> &cellsToOpen){
    for(int i = -1 ; i <= 1 ; i++){
        for(int j = -1 ; j <= 1 ; j++){
            int newRow = row + i;
            int newCol = col + j;
            if((i || j) && isValidPlace(newRow, newCol)){
                BoardCoordinates newCoords;
                newCoords.row = newRow;
                newCoords.column = newCol + (unsigned) 'a';
                cellsToOpen.push(newCoords);
            }
        }
    }

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

void Board::showWholeBoard(){
    for(unsigned row = 0 ; row < sizeVert ; row++){
        for(unsigned col = 0 ; col < sizeHoriz ; col++){
            theBoard[row][col].open();
        }
    }
}
unsigned Board::countUnopened(){
    unsigned unopened = 0;
    for(unsigned row = 0 ; row < sizeVert ; row++)
        for(unsigned col = 0 ; col < sizeHoriz ; col++)
            if(!theBoard[row][col].isOpen())
                unopened++;
    return unopened;
}

bool Board::isValidPlace(int row, int col){
    if(row < 0 || (unsigned)row >= sizeVert)
        return false;
    if(col < 0 || (unsigned)col >= sizeHoriz)
        return false;
    return true;
}

void Board::validateInput(int row, int col){
    if(!isValidPlace(row, col)){
        std::cerr << "Error: Out of bounds\n";
        throw std::out_of_range("Out of bounds\n");
    }
}

void Board::makeBoard(){
    makeRandomBoard();
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

void Board::setNeighbors(){
    for(unsigned row = 0 ; row < sizeVert ; row++){
        for(unsigned col = 0 ; col < sizeHoriz ; col++){
            theBoard[row][col].setNeighbors(getNumNeighbors(row, col));
        }
    }
}

unsigned Board::getNumNeighbors(unsigned row, unsigned col){
    unsigned neighbors = 0;
    unsigned neighborRow;
    unsigned neighborCol;

    for(int i = -1 ; i <= 1 ; i++){
        for(int j = -1 ; j <= 1 ; j++){
            neighborRow = row + i;
            neighborCol = col + j;
            if(isValidPlace(neighborRow, neighborCol) && theBoard[neighborRow][neighborCol].isMine()){
                neighbors++;
            }
        }
    }
    return neighbors;
}
