#include <assert.h>
#include "cell.h"

const char UNOPENED_GFX = '?';
const char FLAGGED_GFX  = 'x';
const char MINE_GFX     = '*';

Cell::Cell(){
    isSet = false;
}

Cell::Cell(bool isAMine, unsigned neighbors){
    setContents(isAMine, neighbors);
}

void Cell::setContents(bool isAMine, unsigned neighbors){
    assert(!isSet);
    this->mine = isAMine;
    this->contents = (this->mine ? MINE_GFX : neighbors + '0');
    curStatus = CLOSED;
    isSet = true;
}

bool Cell::isMine(){
    return mine;
}

bool Cell::canBeOpened(){
    return curStatus == CLOSED ? true : false;
}

bool Cell::isOpen(){
    return curStatus == OPEN ? true : false;
}

void Cell::flag(){
    curStatus = (curStatus == CLOSED ? FLAGGED : CLOSED);
}

void Cell::open(){
    if(curStatus == FLAGGED)
        return;
    curStatus = OPEN;
}

char Cell::getDisplay(){
    switch(curStatus){
        case OPEN: return contents;
        case CLOSED: return UNOPENED_GFX;
        case FLAGGED: return FLAGGED_GFX;
    }
}
