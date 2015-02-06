#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <time.h>
#include "board.h"

#define DEBUG 0

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

    for(unsigned row = 0 ; row < sizeVert ; row++){
        for(unsigned col = 0 ; col < sizeHoriz ; col++){
            // Set cell based on whether a mine or not
            theBoard[row][col].setMine(false);
            theBoard[row][col].setNeighbors(0);
        }
    }
    makeBoard();
    setNeighbors();
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

    // Convert from BoardCoordinates to an integer row/col
    unsigned row = play.row;
    unsigned col = play.column - (unsigned)'a';
    validateInput(row, col);

    if(!theBoard[row][col].canBeOpened())
        return false;

    if(theBoard[row][col].isMine()){
        theBoard[row][col].open();
        return true;
    }

    cellsToOpen.push(play);

    // Stack based approach to opening adjacent cells if the current cell is 0
    while(!cellsToOpen.empty()){
        BoardCoordinates curCell = cellsToOpen.top();
        cellsToOpen.pop();
        row = curCell.row;
        col = curCell.column - (unsigned)'a';

        // If the current square has not already been opened, open it
        if(!theBoard[row][col].isOpen()){
            theBoard[row][col].open();
            // Then add all of its neighbors to the stack, if current square has
            // 0 neighbors
            if(theBoard[row][col].getDisplay() == NUM_GFX[0]){
                addNeighbors(row, col, cellsToOpen);
            }
        }
    }
    return false;
}

void Board::addNeighbors(int row, int col, std::stack<BoardCoordinates> &cellsToOpen){
    // Add the BoardCoordinates of the 8 surrounding neighbors to the
    // cellsToOpen stack
    for(int i = -1 ; i <= 1 ; i++){
        for(int j = -1 ; j <= 1 ; j++){
            int newRow = row + i;
            int newCol = col + j;
            if((i || j) && isValidPlace(newRow, newCol)){ // Don't readd self or cells off board
                BoardCoordinates newCoords;
                newCoords.row = newRow;
                newCoords.column = newCol + (unsigned) 'a';
                cellsToOpen.push(newCoords);
            }
        }
    }
}

void Board::flagCell(BoardCoordinates play){
    // Flags the cell passed in
    unsigned row = play.row;
    unsigned col = play.column - (unsigned)'a';
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
    // Opens the whole board (called when the game is finished)
    for(unsigned row = 0 ; row < sizeVert ; row++)
        for(unsigned col = 0 ; col < sizeHoriz ; col++)
            theBoard[row][col].open();
}
unsigned Board::countUnopened(){
    // Counts how many unopened square there are on the whole board.  Used for
    // checking if the player has won (if unopened == numMines, player has won)
    unsigned unopened = 0;
    for(unsigned row = 0 ; row < sizeVert ; row++)
        for(unsigned col = 0 ; col < sizeHoriz ; col++)
            if(!theBoard[row][col].isOpen())
                unopened++;
    return unopened;
}

bool Board::isValidPlace(int row, int col){
    // Returns true if row, col are within board bounds, false else
    if(row < 0 || (unsigned)row >= sizeVert)
        return false;
    if(col < 0 || (unsigned)col >= sizeHoriz)
        return false;
    return true;
}

void Board::validateInput(int row, int col){
    // Checks if row, col are within board bounds, throws out_of_range exception
    // if not.  Caught by Game::play().
    if(!isValidPlace(row, col)){
        std::cerr << "Error: Out of bounds\n";
        throw std::out_of_range("Out of bounds\n");
    }
}

void Board::makeBoard(){
    // Currently just makes a random board
    // TODO: Parse board from file?
    makeRandomBoard();
}

int RNG(int i){ return rand() % i; } // TODO: Check if this is truly random

void Board::makeRandomBoard(){
    // Generates a random board by first filling an array from
    // 0 to ((sizeVert*sizeHoriz)-1), shuffling that array, then choosing the
    // first numMines from that array, setting those to be mines.
    unsigned boardSize = sizeVert * sizeHoriz;
    std::vector<unsigned> mineLocations(boardSize);
    for(unsigned i = 0; i < boardSize ; i++){
        mineLocations[i] = i;
    }
    std::random_shuffle(mineLocations.begin(), mineLocations.end(), RNG);
    mineLocations.resize(startMines);
    std::sort(mineLocations.begin(), mineLocations.end());

#if DEBUG
    // Prints the locations of the generated mines
    for(unsigned i = 0 ; i < mineLocations.size() ; i++)
        std::cout << mineLocations[i] << " ";
    std::cout << "\n";
#endif

    // Actually set the mines
    for(unsigned i = 0 ; i < mineLocations.size() ; i++){
        unsigned row = mineLocations[i] / sizeHoriz;
        unsigned col = mineLocations[i] % sizeHoriz;
        theBoard[row][col].setMine(true);
    }
}

void Board::setNeighbors(){
    // For each square, set its graphic to be the number of neighbors it has.
    // If the square is a mine, its graphic is left as a mine.
    for(unsigned row = 0 ; row < sizeVert ; row++){
        for(unsigned col = 0 ; col < sizeHoriz ; col++){
            theBoard[row][col].setNeighbors(getNumNeighbors(row, col));
        }
    }
}

unsigned Board::getNumNeighbors(unsigned row, unsigned col){
    // Count the number of neighbors in the 8 adjacent cells.  Doesn't reprocess
    // itself, but this is unnecessary, as if itself is a mine, then the graphic
    // is left as a mine, not as a number
    unsigned neighbors = 0;
    unsigned neighborRow;
    unsigned neighborCol;

    for(int i = -1 ; i <= 1 ; i++){
        for(int j = -1 ; j <= 1 ; j++){
            if(i || j){ // Don't reprocess self
                neighborRow = row + i;
                neighborCol = col + j;
                if(isValidPlace(neighborRow, neighborCol) && theBoard[neighborRow][neighborCol].isMine()){
                    neighbors++;
                }
            }
        }
    }
    return neighbors;
}
