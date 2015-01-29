#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "board.h"

class Game{
    public:
        Game();
        Game(const unsigned seed);

        int play();
    private:
        Board *theBoard;

        BoardCoordinates getInput();

};
#endif
