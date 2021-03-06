#ifndef BOARD_H_DEFINED
#define BOARD_H_DEFINED

#include <vector>
#include <stack>
#include "cell.h"

enum CELL_STATE{OPEN, CLOSED};

struct BoardCoordinates{
    char     column;
    unsigned row;
};

class Board{
    public:
        Board();
        Board(const unsigned sizeHoriz, const unsigned sizeVert, const unsigned numMines, const unsigned seed);
        ~Board();

        bool openCell(BoardCoordinates play); 
        void flagCell(BoardCoordinates play);
        void printBoard();
        void showWholeBoard();
        unsigned countUnopened();
    private:
        Cell **theBoard;

        void makeBoard();
        void makeRandomBoard();
        void setNeighbors();

        unsigned sizeVert;
        unsigned sizeHoriz;
        unsigned startMines;
        unsigned remMines;


        // Helper functions
        bool isValidPlace(int row, int col);
        void validateInput(int row, int col);
        unsigned getNumNeighbors(unsigned row, unsigned col);
        void addNeighbors(int row, int col, std::stack<BoardCoordinates> &cellsToOpen);
};

#endif

