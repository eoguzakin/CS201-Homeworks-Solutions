/*
 * Oğuz Akın
 * 22002893
 * Section 1
 * CS101 Homework 1
 * 22.03.2022
 * */
#include "ParkingSystem.h"
#include "Lot.h"
#include "Car.h"
ParkingSystem::ParkingSystem(){
    lotsArraySize = 0;
    lotsArray = NULL;
}
ParkingSystem::~ParkingSystem(){
    //dtor
    while(lotsArraySize > 0){
        removeLot((*lotsArray[lotsArraySize-1]).getId());
    }
}
void ParkingSystem::removeAllLots(){
    for(int i = lotsArraySize; i > -1; i--){
        removeLot((*lotsArray[i]).getId());
    }
}
bool ParkingSystem::isUnique(int test_id){
    bool truth = false;
    for(int i = 0; i < lotsArraySize; i++){
        truth = (*lotsArray[i]).isUnique(test_id);
    }
    return truth;
}
void ParkingSystem::createLot(int id, int rows, int columns){
    if(isUnique(id)){
        cout<<"Cannot create the parking lot "<< id <<",a lot with this ID already exists" << endl;
    }
    else if((rows > 12 || rows == 0) || (columns > 12 || columns == 0)){
        cout<<"Cannot create the parking lot "<< id <<", dimensions exceed acceptable bounds" << endl;
    }
    else{
        //if the lot array is empty, we create it and add the lot
        Lot** tmp = lotsArray;
        lotsArray = new Lot*[lotsArraySize+1];
        for(int i = 0; i < lotsArraySize; i++){
            lotsArray[i] = tmp[i];
        }/*
        for(int i = 1; i < lotsArraySize; i++){
            delete[] tmp[i];
        }*/
        delete[] tmp;
        lotsArray[lotsArraySize] = new Lot(id, rows, columns);
        lotsArraySize++;
        //if the lot is not empty, we transfer its values to a different array with size 1 more
        //than this. Then we make our lotsArray point to that array
        cout << "Parking lot with ID " << id << " and dimensions (" << rows << "," << columns << ") has been added to the system" << endl;
    }
}
void ParkingSystem::removeLot(int id){//doesnt work
    bool inHere = false;
    int index = -1;
    for(int i = 0; i < lotsArraySize; i++){
        if((*lotsArray[i]).getId() == id) {
            inHere = true;
            index = i;
        }
    }
    if(inHere){
        //we copy everything the next pointer has to previous and delete the last element and --size
        if((*lotsArray[index]).getCarsSize() == -1){
            for(int i = index; i < lotsArraySize-1; i++){
                (*lotsArray[i]).setCarsArray((*lotsArray[i+1]).getCarsAddress(), (*lotsArray[i+1]).getCarsSize());
                (*lotsArray[i]).setNumOfEmptySpaces((*lotsArray[i+1]).getNumOfEmptySpaces());
                (*lotsArray[i]).setRowNum((*lotsArray[i+1]).getRowNum());
                (*lotsArray[i]).setColumnNum((*lotsArray[i+1]).getColumnNum());
                (*lotsArray[i]).setId((*lotsArray[i+1]).getId());
            }
            delete lotsArray[lotsArraySize-1];
            lotsArraySize--;
        }
        else{
            //print the remove car for all of them and then remove the lots
            for(int j = (*lotsArray[index]).getCarsSize()-1; j > -1; j--){
                (*lotsArray[index]).removeCar(j);
            }
            for(int i = index; i < lotsArraySize; i++){
                lotsArray[i] = lotsArray[i+1];
            }
            lotsArraySize--;
        }
        cout << "Lot " << id << " has been successfully removed from the system" << endl;
    }
    else{
        cout << "Lot " << id << " is not in the system" << endl;
    }
}
void ParkingSystem::listLots(){
    if(lotsArraySize == 0)
        cout << "No lots to list" << endl;
    else{
        cout << "List of lots:" << endl;
        for(int i = 0; i < lotsArraySize; i++){
            cout << "ID: " << (*lotsArray[i]).getId() << ", Dim: (";
            cout << (*lotsArray[i]).getRowNum() << "," << (*lotsArray[i]).getColumnNum();
            cout << "), number of empty parking spaces: " << (*lotsArray[i]).getNumOfEmptySpaces() << endl;
        }
    }
}
void ParkingSystem::lotContents(int id){
    int index = -1;
    for(int i = 0; i < lotsArraySize; i++){
        if(id == (*lotsArray[i]).getId()){
            index = i;
            break;
        }
    }
    if(index != -1){
        (*lotsArray[index]).displayContent();
    }
    else{
        cout << "Lot " << id << " is not in the system" << endl;
    }
}
void ParkingSystem::parkCar(int lotId, string location, string carType, int plateNumber){
    bool truth = false;
    int index = -1;
    for(int i = 0; i < lotsArraySize; i++){
        if((*lotsArray[i]).isUnique(lotId)){
            truth = true;
            index = i;
            break;
        }
    }
    if(truth){
        //if the lot is existing, we find the lot to park the car
        (*lotsArray[index]).addCar(location,carType,plateNumber);
    }
    else{
        cout << "Lot " << lotId << " is not in the system" << endl;
    }
}
void ParkingSystem::findCar(int plateNumber){
    int indexLot = -1;
    int indexCar = -1;
    for(int i = 0; i < lotsArraySize; i++){
        indexCar = (*lotsArray[i]).checkCar(plateNumber);
        if(indexCar != -1){
            indexLot = i;
            break;
        }
    }
    if(indexCar != -1 && indexLot != -1){
        Car c = (*lotsArray[indexLot]).getCar(indexCar);
        if(equal(c.getType().begin(), c.getType().end(),"b")){
            cout<<"Heavy-duty car with plate number " << c.getPlateNum();
            cout<<" is at location " << c.getLocation() << ", lot " << (*lotsArray[indexLot]).getId()<<endl;
        }
        else{
            cout<<"Light-duty car with plate number " << c.getPlateNum();
            cout<<" is at location " << c.getLocation() << ", lot " << (*lotsArray[indexLot]).getId()<<endl;
        }
    }
    else{
        cout<<"The car with number plate " << plateNumber << " is not in the system"<<endl;
    }
}
void ParkingSystem::removeCar(int plateNumber){
    int indexLot = -1;
    int indexCar = -1;
    for(int i = 0; i < lotsArraySize; i++){
        indexCar = (*lotsArray[i]).checkCar(plateNumber);
        if(indexCar != -1){
            indexLot = i;
            break;
        }
    }
    if(indexCar != -1 && indexLot != -1){
        (*lotsArray[indexLot]).removeCar(indexCar);
    }
    else{
        cout<<"The car with number plate " << plateNumber << " is not in the system"<<endl;
    }
}
