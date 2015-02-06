#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "board.h"

enum BOARD_ACTION{A_OPEN, A_FLAG};
class Game{
    public:
        Game();
        Game(unsigned seed);
        Game(unsigned sizeH, unsigned sizeV, unsigned mines);
        Game(unsigned sizeH, unsigned sizeV, unsigned mines, unsigned seed);

        int play();
    private:
        unsigned seed;
        unsigned boardCols;
        unsigned boardRows;
        unsigned numMines;
        Board *theBoard;
        unsigned turnNum;

        void remake();
        void init();

        BoardCoordinates getInput();
        BOARD_ACTION getActionInput();
        void showGameOver();
        void showWin();

};
#endif
