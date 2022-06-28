//
// Oğuz Akın
// 22002893
//
#include <iostream>
#include "PuzzleRow.h"
using namespace std;
PuzzleRow::PuzzleRow(int size, int rowindex, int maxsize) {
    this->rowindex = rowindex;
    this->size = size;
    this->maxSize = maxsize;
    head = NULL;
    next = NULL;
}
PuzzleRow::~PuzzleRow() {
    for(int i = 0; i < maxSize; i++){
        remove(i);
    }
}
PuzzleRow* PuzzleRow::getNext() {
    return next;
}
unsigned char PuzzleRow::getPiece(int index) {
    PuzzlePiece* tmp = find(index);
    unsigned char c = 255;
    if(tmp == NULL) {
        return c;
    }
    else {
        return tmp->shape;
    }
}
int PuzzleRow::getRowIndex() {
    return rowindex;
}
PuzzleRow::PuzzlePiece *PuzzleRow::find(int index) {
    for(PuzzlePiece* curr = head; curr != NULL; curr = curr->next){
        if(curr->colindex == index) return curr;
    }
    return NULL;
}
bool PuzzleRow::insert(int index, unsigned char shape) {
    if(index < 0 || index >= maxSize) return false;
    PuzzlePiece* newpiece = new PuzzlePiece;
    newpiece->shape = shape;
    newpiece->rowindex = rowindex;
    newpiece->colindex = index;
    newpiece->next = NULL;
    if(head == NULL) {
        head = newpiece;
    }
    else{
        PuzzlePiece* curr = head;
        for(; curr->next != NULL; curr = curr->next){}
        curr->next = newpiece;
    }
    size++;
    return true;
}
bool PuzzleRow::isEmpty() {
    return (size == 0);
}
void PuzzleRow::printRow() {
    for(int i = 0; i < maxSize; i++){
        PuzzlePiece* curr = find(i);
        if(curr != NULL && i == curr->colindex){
            cout<<"X";
        }
        else{
            cout<<"O";
        }
    }
}
bool PuzzleRow::remove(int index) {
    if(index < 0 || index >= maxSize) return false;
    PuzzlePiece* curr = find(index);
    if(curr != NULL){
        if(curr == head){
            PuzzlePiece* tmp = head->next;
            delete head;
            head = tmp;
            size--;
            return true;
        }
        else{
            for(PuzzlePiece* prev = head; prev->next != NULL; prev = prev->next){
                if(prev->next == curr){
                    prev->next = curr->next;
                    delete curr;
                    size--;
                    return true;
                }
            }
        }
    }
    return false;
}
void PuzzleRow::setNext(PuzzleRow *next) {
    this->next = next;
}
