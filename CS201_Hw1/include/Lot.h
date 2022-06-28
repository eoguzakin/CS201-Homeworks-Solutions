#ifndef LOT_H
#define LOT_H
/*
 * Oğuz Akın
 * 22002893
 * Section 1
 * CS101 Homework 1
 * 22.03.2022
 * */
#include "Car.h"
#include <iostream>

class Lot
{
    public:
        Lot(int lot_idz, int d1, int d2);
        ~Lot();
        bool isUnique(int test_id);
        bool isParkable(string loc, string typ, int plate);
        int getId();
        int getNumOfEmptySpaces();
        int getRowNum();
        int getColumnNum();
        int isCarThere(int r, int c);
        int checkCar(int plate);
        int carToDraw(int r, int c);
        int getCarsSize();
        void setId(int i);
        void setNumOfEmptySpaces(int es);
        void setRowNum(int r);
        void setColumnNum(int c);
        void addCar(string loc, string typ, int plate);
        void displayContent();
        void removeCar(int indexCar);
        void removeAllCars();
        void setCarsArray(Car** a, int asize);
        void setCarsSize(int size);
        Car getCar(int carindex);
        Car** getCarsAddress();
    private:
        int id;
        int emptySpaces;
        int lotDsize1;
        int lotDsize2;
        int carsSize;
        char** carlot;
        Car** cars;
};

#endif // LOT_H
