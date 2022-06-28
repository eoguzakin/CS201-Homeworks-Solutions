#include <iostream>
using namespace std;
#include "Solutions.h"
int main() {
    cout << endl;
    cout << "Testing Fantabulous" << endl;
    cout << endl;
    fantabulous("1,7,4,12,14",5);
    fantabulous("1,15,2,5,12,14",6);
    fantabulous("3,4,12,18,21,100,4,2,1,99",10);
    cout << endl;
    cout << "Testing Subset Problem" << endl;
    cout << endl;
    subset("1,7,10,12,11,17,15,16,19,22",10);
    subset("3,6,4,12,15,19,21,25,21,44,45,47,90,92",14);
    subset("2,4,3,10,12,18,19,20",8);
    cout << endl;
    cout << "Testing Infix to Prefix" << endl;
    cout << endl;
    cout << infix2prefix("(7-2)*3-(4/2)+6") << endl;
    cout << infix2prefix("9/2-(6-4)*2+9") << endl;
    cout << infix2prefix("9/3+6/2-(4-2)") << endl;
    cout << endl;
    cout << "Testing evaluate Prefix" << endl;
    cout << endl;
    evaluatePrefix("-*-7236");
    evaluatePrefix("-/92+*-6429");
    evaluatePrefix("+/93-/62-42");
    return 0;
}
