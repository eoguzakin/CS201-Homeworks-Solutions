//
// Oğuz Akın
// 22002893
//
#include "PuzzleRow.h"
#ifndef CS201_HW3_PUZZLECONTAINER_H
#define CS201_HW3_PUZZLECONTAINER_H
inline void shapeConverter(unsigned char shape, int& down, int& up, int& right, int& left){
    down = shape%4;
    up = (shape/4)%4;
    right= (shape/16)%4;
    left= shape/64;
}
class PuzzleContainer{
private:
    PuzzleRow* rowLists;
    int height;
    int width;
    unsigned char getPiece(int row, int col);
    bool isRowUnique(int row);
    void translator(int &h, int &w);
    bool isFit(int row, int col, unsigned char shape);
public:
    PuzzleContainer( int h, int w);
    ~PuzzleContainer();
    PuzzleRow* getRow( int index );
    bool insertRow( int index );
    bool removeRow( int index );
    bool addPiece( int row, int col , char shape );
    bool removePiece(int row, int col);
    int getHeight();
    int getWidth();
    void showPiece(int row, int col);
    void displayContainer();
    void showColumn(int col);
    void showRow(int row);
    void findPiece(char shape);
};
#endif //CS201_HW3_PUZZLECONTAINER_H
