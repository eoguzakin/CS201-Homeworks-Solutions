//
//  Oğuz Akın
//  22002893

#ifndef CS201_HW4_SOLUTIONS_H
#define CS201_HW4_SOLUTIONS_H
using namespace std;

#include <iostream>
#include <string>
#include <sstream>
#include "Stack.h"
#include "Interval.h"

void fantabulous(string list, int length);
bool isFantabulous(Stack<int> &s);
bool precedence(char in, char st);
void subset(string intervals, int length);
string infix2prefix(string expression);
void evaluatePrefix(string expression);

#endif //CS201_HW4_SOLUTIONS_H
