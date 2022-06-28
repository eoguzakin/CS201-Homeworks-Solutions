//
// Oğuz Akın
// 22002893
//
#include <iostream>
#include "PuzzleContainer.h"
using namespace std;
PuzzleContainer::PuzzleContainer(int h, int w) {
    height = h;
    width = w;
    rowLists = NULL;
}
PuzzleContainer::~PuzzleContainer() {
    for(int i = 0; i < height; i++){
        removeRow(i);
    }
    delete rowLists;
}
void PuzzleContainer::translator(int &h, int &w){
    h--;w--;
}
bool PuzzleContainer::isFit(int row, int col, unsigned char shape){
    int up,down,left,right;
    shapeConverter(shape,down,up,right,left);
    int cup = -1,cdown = -1,cleft = -1,cright = -1,dummy = -1;//they are -1 if there is no piece there or is border
    PuzzleRow*prev = getRow(row-1);
    PuzzleRow*curr = getRow(row);
    PuzzleRow*next = getRow(row+1);
    if(prev == NULL){//left right check
        unsigned char leftpiece = curr->getPiece(col-1);
        shapeConverter(leftpiece,dummy,dummy,cleft,dummy);
        unsigned char rightpiece = curr->getPiece(col+1);
        shapeConverter(rightpiece,dummy,dummy,dummy,cright);
        if(next != NULL){//down check
            unsigned char downpiece = next->getPiece(col);
            shapeConverter(downpiece,dummy,cdown,dummy,dummy);
        }
    }
    else{//up left right check
        unsigned char uppiece = prev->getPiece(col);
        shapeConverter(uppiece,cup,dummy,dummy,dummy);
        unsigned char leftpiece = curr->getPiece(col-1);
        shapeConverter(leftpiece,dummy,dummy,cleft,dummy);
        unsigned char rightpiece = curr->getPiece(col+1);
        shapeConverter(rightpiece,dummy,dummy,dummy,cright);
        if(next != NULL){//down check
            unsigned char downpiece = next->getPiece(col);
            shapeConverter(downpiece,dummy,cdown,dummy,dummy);
        }
    }
    //BORDER CHECKS
    if(row == 0 && up != 2)return false;
    else if(row == height-1 && down != 2)return false;
    else if(col == 0 && left != 2)return false;
    else if(col == width-1 && right != 2)return false;
    if(!(row == 0 || row == height-1) && (up == 2 || down == 2))return false;
    else if(!(col == 0 || col == width-1) && (right == 2 || left == 2))return false;
    else{
        if((left != 2 && cleft == 2))return false;//as there is no piece at left, char is 255 and its right is 3
        else if(left == cleft)return false;//as the pieces dont have the same extension and its not on border, they are KNOB-HOLE
        if((right != 2 && cright == 2))return false;
        else if(right == cright)return false;
        if((up != 2 && cup == 2))return false;
        else if(up == cup)return false;
        if((down != 2 && cdown == 2))return false;
        else if(down == cdown)return false;
    }
    return true;
}
bool PuzzleContainer::addPiece(int r, int c, char shape) {
    int row = r; int col = c;
    translator(row,col);
    if(row >= height || col >= width || row < 0 || col < 0){
        cout<<"("<<r<<","<<c<<") is out of frame, it cannot be added"<<endl;
        return false;
    }
    else if(getPiece(row,col) != 255){
        cout<<"("<<r<<","<<c<<") is already occupied, it cannot be added"<<endl;
    }
    else{
        if(isRowUnique(row)){//no rows before that index
            insertRow(row);//lost memory
        }
        if(isFit(row,col,shape)){
            getRow(row)->insert(col,shape);
            cout<<"A piece is addded to ("<<r<<","<<c<<")"<<endl;
        }
        else{
            cout<<"Shape doesn't fit into ("<<r<<","<<c<<"), it cannot be added"<<endl;
        }
    }
    return true;
}
bool PuzzleContainer::removePiece(int r, int c) {
    int row = r; int col = c;
    translator(row,col);
    if(row >= height || col >= width || row < 0 || col < 0){
        cout<<"("<<r<<","<<c<<") is out of frame, it cannot be removed"<<endl;
        return false;
    }
    else if(!isRowUnique(row)){
        if(getRow(row)->remove(col)){
            if(getRow(row)->isEmpty()){
                removeRow(row);
            }
            cout<<"The piece on ("<<r<<","<<c<<") is removed"<<endl;
            return true;
        }
        else{//there is no piece at this row
            cout<<"There is no piece on ("<<r<<","<<c<<"), it cannot be removed"<<endl;
            return false;
        }
    }
    else{//row dne therefore there is no piece there
        cout<<"There is no piece on ("<<r<<","<<c<<"), it cannot be removed"<<endl;
        return false;
    }
}
bool PuzzleContainer::insertRow(int index) {
    if(index >= height) return false;
    else{
        if(rowLists == NULL){
            rowLists = new PuzzleRow(0,index,width);//lost memory
        }
        else{
            PuzzleRow* curr = new PuzzleRow(0,index,width);
            PuzzleRow* tmp = rowLists;
            for(; tmp->getNext() != NULL; tmp = tmp->getNext()){}
            tmp->setNext(curr);
            curr->setNext(NULL);
        }
    }
    return true;
}
bool PuzzleContainer::removeRow(int index) {
    if(index < 0 || index > height) return false;
    if(!isRowUnique(index)){
        PuzzleRow* tmp = getRow(index);
        for(PuzzleRow* prev = rowLists; prev != NULL; prev = prev->getNext()){
            if(prev->getNext() == tmp){
                prev->setNext(tmp->getNext());
                delete tmp;
                return true;
            }
        }
    }
    return false;
}
bool PuzzleContainer::isRowUnique(int row){
    if(rowLists != NULL){
        for(PuzzleRow*curr = rowLists; curr != NULL; curr = curr->getNext()){
            if(curr->getRowIndex() == row){
                return false;
            }
        }
    }
    return true;
}
unsigned char PuzzleContainer::getPiece(int row, int col){
    if(row >= height || col >= width || row < 0 || col < 0){
        return 255;
    }
    else if(!isRowUnique(row)){
        PuzzleRow* curr = rowLists;
        for(; curr != NULL; curr = curr->getNext()){
            if(curr->getRowIndex() == row) break;
        }
        return curr->getPiece(col);
    }
    else{
        return 255;
    }
}
void PuzzleContainer::findPiece(char shape) {
    bool found = false;
    for(PuzzleRow* curr = rowLists; curr != NULL; curr = curr->getNext()){
        for(int j = 0; j < width; j++){
            unsigned char c = curr->getPiece(j);
            if(c == shape){
                cout<<"("<<curr->getRowIndex()+1<<","<<j+1<<"), ";
                found = true;
            }
        }
    }
    if(found) cout<<"contain the piece that has shape"<<endl;
    else cout<<"There is no piece that has shape"<<endl;
    int up,down,left,right;
    shapeConverter(shape,down,up,right,left);
    if(down == 0){
        cout<<"Down: Hole"<<endl;
    }
    else if(down == 1){
        cout<<"Down: Knob"<<endl;
    }
    else if(down == 2){
        cout<<"Down: Border"<<endl;
    }
    if(up == 0){
        cout<<"Up: Hole"<<endl;
    }
    else if(up == 1){
        cout<<"Up: Knob"<<endl;
    }
    else if(up == 2){
        cout<<"Up: Border"<<endl;
    }
    if(right == 0){
        cout<<"Right: Hole"<<endl;
    }
    else if(right == 1){
        cout<<"Right: Knob"<<endl;
    }
    else if(right == 2){
        cout<<"Right: Border"<<endl;
    }
    if(left == 0){
        cout<<"Left: Hole"<<endl;
    }
    else if(left == 1){
        cout<<"Left: Knob"<<endl;
    }
    else if(left == 2){
        cout<<"Left: Border"<<endl;
    }
}
void PuzzleContainer::displayContainer() {
    cout<<"Container "<<height<<"x"<<width<<":"<<endl;
    cout<<" ";
    for(int i = 0; i < width; i++){
        cout<<i+1;
    }cout<<endl;
    for(int i = 0; i < height; i++){
        cout<<i+1;
        PuzzleRow* curr = getRow(i);
        if(curr == NULL){
            for(int j = 0; j < width; j++){
                cout<<"O";
            }
        }
        else{
            curr->printRow();
        }
        cout<<endl;
    }
}
void PuzzleContainer::showColumn(int col) {
    col--;
    if(0 > col || col > width){
        cout<<"Column "<<col+1<<" is out of border"<<endl;
    }
    else if(rowLists != NULL){
        cout<<"Column "<<col+1<<":"<<endl;
        for(PuzzleRow* curr = rowLists; curr != NULL; curr = curr->getNext()){
            char c = curr->getPiece(col);
            if(c == -1){//cant make 255
                cout<<"O"<<endl;
            }
            else cout<<"X"<<endl;
        }
    }
    else{
        cout<<"Nothing to show"<<endl;
    }
}
void PuzzleContainer::showPiece(int r, int c) {
    int row = r; int col = c;
    translator(row,col);
    if(row >= height || col >= width || row < 0 || col < 0){
        cout<<"("<<r<<","<<c<<") is out of frame, it cannot be shown"<<endl;
    }
    else{
        int up,down,left,right;
        unsigned char sh = getPiece(row,col);
        if(sh == 255){
            cout<<"There is no piece on ("<<r<<","<<c<<"), it cannot be shown"<<endl;
        }
        else{
            shapeConverter(sh,down,up,right,left);
            cout<<"Piece on ("<<r<<","<<c<<") as following:"<<endl;
            if(down == 0){
                cout<<"Down: Hole"<<endl;
            }
            else if(down == 1){
                cout<<"Down: Knob"<<endl;
            }
            else if(down == 2){
                cout<<"Down: Border"<<endl;
            }
            if(up == 0){
                cout<<"Up: Hole"<<endl;
            }
            else if(up == 1){
                cout<<"Up: Knob"<<endl;
            }
            else if(up == 2){
                cout<<"Up: Border"<<endl;
            }
            if(right == 0){
                cout<<"Right: Hole"<<endl;
            }
            else if(right == 1){
                cout<<"Right: Knob"<<endl;
            }
            else if(right == 2){
                cout<<"Right: Border"<<endl;
            }
            if(left == 0){
                cout<<"Left: Hole"<<endl;
            }
            else if(left == 1){
                cout<<"Left: Knob"<<endl;
            }
            else if(left == 2){
                cout<<"Left: Border"<<endl;
            }
        }
    }
}
void PuzzleContainer::showRow(int row) {
    row--;
    if(row < 0 || row >= height){
        cout<<"Row "<<row+1<<" is out of border"<<endl;
    }
    else{
        cout<<"Row "<<row+1<<":"<<endl;
        getRow(row)->printRow();
    }
}
PuzzleRow* PuzzleContainer::getRow(int index) {
    for(PuzzleRow* curr = rowLists; curr != NULL; curr = curr->getNext()){
        if(curr->getRowIndex() == index){
            return curr;
        }
    }
    return NULL;
}
int PuzzleContainer::getHeight() {
    return height;
}
int PuzzleContainer::getWidth() {
    return width;
}