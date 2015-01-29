#include <iostream>
#include "game.h"
#include "board.h"

int main(){
    Game g(10);
    g.play();
    //Board f(15, 15, 5, 0);
    //f.printBoard();
    //std::cout << f.openCell('b', 2) << "\n";
    //std::cout << f.openCell('a', 0) << "\n";
    //f.flagCell('c', 4);
    //f.printBoard();
    return 0;
}

