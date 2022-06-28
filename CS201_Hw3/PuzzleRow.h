//
// Oğuz Akın
// 22002893
//

#ifndef CS201_HW3_PUZZLEROW_H
#define CS201_HW3_PUZZLEROW_H
class PuzzleRow{
private:
    struct PuzzlePiece{
        unsigned char shape;
        int rowindex;
        int colindex;
        PuzzlePiece* next;
    };
    PuzzlePiece* head;
    PuzzleRow* next;
    PuzzlePiece* find(int index);
    int rowindex;
    int size;
    int maxSize; //equals to puzzleContainer width
public:
    PuzzleRow( int size, int rowindex, int maxsize);
    ~PuzzleRow();
    int getRowIndex();
    void setNext( PuzzleRow* next );
    PuzzleRow* getNext();
    bool insert( int index, unsigned char shape );
    bool remove( int index );
    bool isEmpty();
    unsigned char getPiece(int index );
    void printRow();
};
#endif //CS201_HW3_PUZZLEROW_H
