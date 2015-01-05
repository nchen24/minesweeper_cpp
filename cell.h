
class Cell{
    enum STATUS {OPEN, CLOSED, FLAGGED};

    public:
        Cell();
        Cell(bool isAMine, unsigned neighbors);
        void setContents(bool isAMine, unsigned neighbors);

        bool isMine();
        bool canBeOpened();
        bool isOpen();

        char getDisplay();
        
        void flag();
        void open();
    private:
        bool mine;
        char contents;

        bool isSet;

        STATUS curStatus;
};
