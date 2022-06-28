/*
 * Oğuz Akın
 * 22002893
 * Section 1
 * CS101 Homework 1
 * 22.03.2022
 * */
#include <string>
#include <sstream>
using namespace std;
#ifndef CS201_HW1_CAR_H
#define CS201_HW1_CAR_H
class Car
{
public:
    Car(string loc, string typ, int plate);
    ~Car();
    string getLocation();
    string getType();
    int getPlateNum();
    int getRow();
    int getCol();
    void setLocation(string loc);
    void setType(string typ);
    void setPlateNum(int plate);
    bool isUnique(int plat);
private:
    string location;
    string type;
    int plateNum;
    int row;
    int col;
};
#endif //CS201_HW1_CAR_H
