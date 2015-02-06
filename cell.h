#ifndef CELL_H_DEFINED
#define CELL_H_DEFINED

const char UNOPENED_GFX = '?';
const char FLAGGED_GFX  = 'x';
const char MINE_GFX     = '*';
const char EMPTY_GFX    = '0';

class Cell{
    enum STATUS {OPEN, CLOSED, FLAGGED};

    public:
        Cell();
        Cell(bool isAMine, unsigned neighbors);
        void setMine(bool isAMine);
        void setNeighbors(unsigned neighbors);

        bool isMine();
        bool canBeOpened();
        bool isOpen();

        char getDisplay();
        
        void flag();
        void open();
    private:
        bool mine;
        char contents;


        bool isSet();
        bool mineSet;
        bool neighborsSet;

        STATUS curStatus;
};

#endif
