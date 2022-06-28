/*
 * Oğuz Akın
 * 22002893
 * Section 1
 * CS101 Homework 1
 * 22.03.2022
 * */
#include "Car.h"
using namespace std;
Car::Car(string loc, string typ, int plate){
    location = loc;
    type = typ;
    plateNum = plate;
    row = -1;
    string target = loc.substr(1);
    istringstream(target) >> col;
    col--;
    row = (int)(loc[0]) - 65;
}
Car::~Car() {
}
string Car::getLocation(){
    return location;
}
string Car::getType(){
    return type;
}
int Car::getPlateNum(){
    return plateNum;
}
int Car::getRow() {
    return row;
}
int Car::getCol() {
    return col;
}
void Car::setLocation(string loc){
    location = loc;
    //doesnt come here, cant assign the passed to loc to this one for last car
}
void Car::setType(string typ){
    type = typ;
}
void Car::setPlateNum(int plate){
    plateNum = plate;
}
bool Car::isUnique(int plat){
    return plat == plateNum;
}
