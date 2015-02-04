#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "board.h"

class Game{
    public:
        Game();
        Game(unsigned seed);

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
        void showGameOver();

};
#endif
