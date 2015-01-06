#include <vector>
#include "cell.h"

enum CELL_STATE{OPEN, CLOSED};
const char UNOPENED_GFX = '?';
const char FLAGGED_GFX  = 'x';
const char MINE_GFX     = '*';

class Board{
    public:
        Board();
        Board(const unsigned sizeHoriz, const unsigned sizeVert, const unsigned numMines, const unsigned seed);
        ~Board();

        bool openCell(const char x, const int y); 
        void flagCell(const char x, const int y);
        void printBoard();
    private:
        Cell **theBoard;

        unsigned sizeVert;
        unsigned sizeHoriz;
        unsigned startMines;
        unsigned remMines;


        // Helper functions
        void validateInput(const unsigned row, const unsigned col);
};
