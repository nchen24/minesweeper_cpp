#include <assert.h>
#include "cell.h"

#define BOARDVIS 0


Cell::Cell(){
    curStatus = CLOSED;
    mineSet = false;
    neighborsSet = false;
}

Cell::Cell(bool isAMine, unsigned neighbors){
    setMine(isAMine);
    setNeighbors(neighbors);
    curStatus = CLOSED;
}

void Cell::setMine(bool isAMine){
    this->mine = isAMine;
    mineSet = true;
}

void Cell::setNeighbors(unsigned neighbors){
    this->contents = (this->mine ? MINE_GFX : neighbors + '0');
    if(this->contents == '0')
        this-> contents = EMPTY_GFX;
    neighborsSet = true;
}

bool Cell::isSet(){
    return mineSet && neighborsSet;
}

bool Cell::isMine(){
    return mine;
}

bool Cell::canBeOpened(){
    switch(curStatus){
        case OPEN:      return false;
        case CLOSED:    return true;
        case FLAGGED:   return false;
    }
}

bool Cell::isOpen(){
    return curStatus == OPEN ? true : false;
}

void Cell::flag(){
    curStatus = (curStatus == CLOSED ? FLAGGED : CLOSED);
    this->contents = FLAGGED_GFX;
}

void Cell::open(){
    if(curStatus == FLAGGED)
        return;
    curStatus = OPEN;
}

char Cell::getDisplay(){
#if BOARDVIS 
    return mine ? MINE_GFX : contents;
#endif
    switch(curStatus){
        case OPEN:    return contents;
        case CLOSED:  return UNOPENED_GFX;
        case FLAGGED: return FLAGGED_GFX;
    }
}
