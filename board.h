#include <vector>

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
        CELL_STATE **boardState; // Whether or 
        bool **boardContents;
        char **boardDisplay;

        int sizeVert;
        int sizeHoriz;
        int startMines;
        int remMines;


        // Helper functions
        void validateInput(const int row, const int col);


};
