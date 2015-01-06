#include <iostream>
#include "board.h"

int main(){
    Board f(15, 15, 5, 0);
    f.printBoard();
    std::cout << f.openCell('b', 2) << "\n";
    std::cout << f.openCell('a', 0) << "\n";
    f.flagCell('c', 4);
    f.printBoard();
    return 0;
}
