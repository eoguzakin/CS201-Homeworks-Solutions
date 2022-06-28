#include "Lot.h"
#include "Car.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
Lot::Lot(const int lot_id,const int d1,const int d2)
{
    id = lot_id;
    lotDsize1 = d1;
    lotDsize2 = d2;
    emptySpaces = lotDsize1 * lotDsize2;
    carsSize = -1;
    cars = NULL;
}
Lot::~Lot()
{
    //dtor
    if(carsSize > -1){
        removeAllCars();
        delete[] cars;
    }
}
void Lot::removeAllCars(){
    for(int indexCar = carsSize-1; indexCar > -1; indexCar--){
        for(int i = indexCar; i < carsSize-1; i++){
        (*cars[i]).setPlateNum((*cars[i+1]).getPlateNum());
        (*cars[i]).setLocation((*cars[i+1]).getLocation());
        (*cars[i]).setType((*cars[i+1]).getType());
        }
        if(carsSize>0){
        delete cars[carsSize-1];
        carsSize--;
        }
    }
    carsSize = -1;
}
void Lot::removeCar(int indexCar){
    //we copy everything the next pointer has to previous and delete the last element and --size
    if(!(*cars[indexCar]).getType().compare("b")){
        cout<<"Heavy-duty car";
        emptySpaces+=2;
    }
    else{
        cout<<"Light-duty car";
        emptySpaces++;
    }
    cout<<" with number plate " << (*cars[indexCar]).getPlateNum();
    cout<< " car has been removed from slot " << (*cars[indexCar]).getLocation();
    cout<<", lot "<<id<<endl;
    for(int i = indexCar; i < carsSize-1; i++){
        (*cars[i]).setPlateNum((*cars[i+1]).getPlateNum());
        (*cars[i]).setLocation((*cars[i+1]).getLocation());
        (*cars[i]).setType((*cars[i+1]).getType());
    }
    if(carsSize>0){
        delete cars[carsSize-1];
        carsSize--;
    }
}
int Lot::getId(){
    return id;
}
int Lot::getNumOfEmptySpaces(){
    return emptySpaces;
}
int Lot::getRowNum(){
    return lotDsize1;
}
int Lot::getColumnNum(){
    return lotDsize2;
}
void Lot::setId(int i){
    id = i;
}
void Lot::setNumOfEmptySpaces(int es){
    emptySpaces = es;
}
void Lot::setRowNum(int r){
    lotDsize1 = r;
}
void Lot::setColumnNum(int c){
    lotDsize2 = c;
}
bool Lot::isUnique(int test_id) {
    return test_id == id;
}
int Lot::checkCar(int plate){
    for(int i = 0; i < carsSize; i++){
        if((*cars[i]).getPlateNum() == plate){
            return i;
        }
    }
    return -1;
}
Car Lot::getCar(int carindex){
    return *cars[carindex];
}
Car** Lot::getCarsAddress(){
    return cars;
}
void Lot::setCarsArray(Car** a, int asize){
    for(int i = carsSize; i > -1; i--){
        delete cars[i];
    }
    delete[] cars;
    cars = a;
    carsSize = asize;
}
void Lot::setCarsSize(int size){
    carsSize = size;
}
int Lot::getCarsSize(){
    return carsSize;
}
bool Lot::isParkable(string loc, string typ, int plate){
    //we first find the specified row and col from the first char
    int row = -1;
    int col = -1;
    string target = loc.substr(1);
    istringstream(target) >> col;
    col--;
    row = (int)(loc[0]) - 65;
    if(row >= 0 && col >= 0 && row < lotDsize1 && col < lotDsize2){
        if(std::equal(typ.begin(), typ.end(),"a")){
            //we check for total emptyness
            if(emptySpaces == lotDsize1 * lotDsize2){
                carsSize = 0;
                return true;
            }
            //check location emptyness for a type car
            bool empty = true;
            if(isCarThere(row,col) != -1){
                empty = false;
            }
            //if empty we check the plate num
            if(empty){
                for(int i = 0; i < carsSize; i++){
                    if(plate == (*cars[i]).getPlateNum()){
                        empty = false;
                    }
                }
                if(!empty){
                    cout << "Cannot park light-duty car with number plate ";
                    cout << plate << " at location " << loc << ", a car with same plate number exists" << endl;
                }
            }
            else{
                cout << "Cannot park light-duty car with number plate ";
                cout << plate << " at location " << loc << ", already occupied" << endl;
            }
            return empty;
        }
        else if(equal(typ.begin(), typ.end(),"b")){
            if(row > 0){//we check for total emptyness
                if(emptySpaces == lotDsize1 * lotDsize2){
                    carsSize = 0;
                    return true;
                }
                //check locations with this and previous row for b type car
                bool empty = true;
                if(isCarThere(row,col) != -1){
                    empty = false;
                }
                if(empty){
                    for(int i = 0; i < carsSize; i++){
                        if(plate == (*cars[i]).getPlateNum()){
                            empty = false;
                        }
                    }
                    if(!empty){
                        cout << "Cannot park heavy-duty car with number plate ";
                        cout << plate << " at location " << loc << ", a car with same plate number exists" << endl;
                    }
                }
                else{
                    cout << "Cannot park heavy-duty car with number plate ";
                    cout << plate << " at location " << loc << ", already occupied" << endl;
                }
                return empty;}
            else{
                cout << "Cannot park heavy-duty car with number plate ";
                cout << plate << " at location " << loc << ", not enough space" << endl;
            }
        }
        else{
            cout << "Cannot park invalid car type with number plate ";
            cout << plate << " at location " << loc << endl;

        }
        return false;
    }
    else{
        if(equal(typ.begin(), typ.end(),"a")){
            cout << "Cannot park light-duty car with number plate ";
            cout << plate << " at location " << loc << ", out of bounds" << endl;
        }
        else if(equal(typ.begin(), typ.end(),"b")){
            cout << "Cannot park heavy-duty car with number plate ";
            cout << plate << " at location " << loc << ", out of bounds" << endl;
        }
    }
    return false;
}
void Lot::addCar(string loc, string typ, int plate){
    if(isParkable(loc,typ,plate)){
        Car** carr = cars;
        cars = new Car*[carsSize+1];
        for(int i = 0; i < carsSize; i++){
            cars[i] = carr[i];
        }
        delete[] carr;
        cars[carsSize] = new Car(loc,typ,plate);
        carsSize++;
        if(equal(typ.begin(), typ.end(),"a")){
            emptySpaces--;
            cout << "Light-duty car with number plate " << plate;
            cout << " has been parked at location " << loc << ", lot " << id << endl;
        }
        else{
            emptySpaces-=2;
            cout << "Heavy-duty car with number plate " << plate;
            cout << " has been parked at location " << loc << ", lot " << id << endl;
        }
    }
}
int Lot::isCarThere(int r, int c){
    int val = -1;
    for(int i = 0; i < carsSize; i++){
        if(!(*cars[i]).getType().compare("a")){
            if(r == (*cars[i]).getRow() && c == (*cars[i]).getCol()){
                val = i;
                break;
            }
        }
        else if((r == (*cars[i]).getRow() || r == (*cars[i]).getRow()-1) && c == (*cars[i]).getCol()){
            val = i;
            break;
        }

    }
    return val;
}
int Lot::carToDraw(int r, int c){
    int val = -1;
    for(int i = 0; i < carsSize; i++){
        if(!(*cars[i]).getType().compare("a")){
            if(r == (*cars[i]).getRow() && c == (*cars[i]).getCol()){
                val = i;
                break;
            }
        }
        else if(r == (*cars[i]).getRow()  && c == (*cars[i]).getCol()){
            val = i;
            break;
        }
    }
    return val;
}
void Lot::displayContent(){
    cout<<"ID: "<<id<<", ("<<lotDsize1<<","<<lotDsize2<<"), empty slots: "<<emptySpaces;
    cout<<", parked cars: ";
    if(carsSize > 0){
        cout<<(*cars[0]).getPlateNum();
        for(int i = 1; i < carsSize; i++){
            cout<<", "<<(*cars[i]).getPlateNum();
        }
    }
    else{
        cout<<"no cars yet";
    }
    cout<<endl<<endl;
    //we fill the char array
    char carlot[lotDsize1][lotDsize2];
    for(int i = 0; i < lotDsize1; i++){
        for(int j = 0; j < lotDsize2; j++){
            int index = carToDraw(i,j);
            if(index != -1){
                if(!(*cars[index]).getType().compare("b")){
                    carlot[i-1][j] = 'b';
                    carlot[i][j] = 'b';
                }
                else{
                    carlot[i][j] = 'a';
                }
            }
            else{
                //can't access this as well
                carlot[i][j] = '+';
            }
        }
    }
    //printing
    cout<<" ";
    for(int i = 1; i <= lotDsize2; i++)
        cout<<" "<<i;
    cout<<endl;
    char letter = 65;
    for(int i = 0; i < lotDsize1; i++){
        cout<<letter;
        for(int j = 0; j < lotDsize2; j++){
            cout<<" "<<carlot[i][j];
            if(j > 8){
                cout<<" ";
            }
        }
        letter++;
        cout<<endl;
    }
}

