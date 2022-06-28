#ifndef PARKINGSYSTEM_H
#define PARKINGSYSTEM_H
/*
 * Oğuz Akın
 * 22002893
 * Section 1
 * CS101 Homework 1
 * 22.03.2022
 * */
#include "Lot.h"
#include "Car.h"
class ParkingSystem{
public:
    ParkingSystem();
    ~ParkingSystem();
    void createLot(int id, int rows, int columns);
    void removeLot(int id);
    void listLots();
    void lotContents(int id);
    void parkCar(int lotId, string location, string carType, int plateNumber);
    void findCar(int plateNumber);
    void removeCar(int plateNumber);
    void removeAllLots();
    bool isUnique(int test_id);
private:
    Lot** lotsArray;
    int lotsArraySize;
// ...
//you may define additional member functions and data members, if necessary
};

#endif // PARKINGSYSTEM_H
