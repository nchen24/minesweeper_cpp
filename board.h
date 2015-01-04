#include <vector>

enum CELL_STATE{MINE, EMPTY};
const char EMPTY_GFX = '?';
const char FLAGGED_GFX = 'x';

class Board{
    public:
        Board();
        Board(const unsigned sizeHoriz, const unsigned sizeVert, const unsigned numMines, const unsigned seed);
        ~Board();

        int openCell(char x, int y);
        void printBoard();
    private:
        bool **boardContents;
        char **boardDisplay;

        int sizeVert;
        int sizeHoriz;
        int startMines;
        int remMines;

        //std::vector<std::vector<CELL_STATE> > theBoard;


};
