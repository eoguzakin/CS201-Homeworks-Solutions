//
//  Oğuz Akın
//  22002893
#include "Solutions.h"
void fantabulous(string list, int length) {
    int nums[length];
    int index = 0;
    int fanta = 0;
    stringstream ss;
    string tmp = "";
    for (int i = 0; i < list.length() + 1; i++) {
        if ((list[i] != ',' || i == list.length()) && list[i] != '\0') {
            tmp += list[i];
        } else {
            ss << tmp;
            ss >> nums[index];
            tmp = "";
            index++;
            ss.clear();
        }
    }
    Stack<int> in,sub;
    for(int i = 0; i < length; i++){
        in.push(nums[i]);
    }
    while(!in.isEmpty()){
        int num1;
        in.pop(num1);
        sub.push(num1);
        while(!in.isEmpty()){
            int num2;
            in.pop(num2);
            sub.push(num2);
            if(isFantabulous(sub)){
                fanta++;
            }
        }
        while(!sub.isEmpty()){
            sub.pop(num1);
            in.push(num1);
        }
        in.pop();
        length--;
    }
    cout<<"The number of Fantabulous subsequences: "<<fanta<<endl;
}
bool isFantabulous(Stack<int> &s){
    Stack<int> inv;
    int max = 0,indexmax = 0,max2 = 0,indexmax2 = 0,count = 0;
    while(!s.isEmpty()){
        int pop;
        s.pop(pop);
        if(pop > max){
            indexmax2 = indexmax;
            indexmax = count;
            max2 = max;
            max = pop;
        }
        else if(pop < max && pop > max2){
            max2 = pop;
            indexmax2 = count;
        }
        inv.push(pop);
        count++;
    }
    while(!inv.isEmpty()){
        inv.pop(max);
        s.push(max);
    }
    return (indexmax2 < indexmax);
}
void subset(string intervals, int length) {
    int nums[length];
    int index = 0;
    stringstream ss;
    string tmp = "";
    for (int i = 0; i < intervals.length() + 1; i++) {
        if ((intervals[i] != ',' || i == intervals.length()) && intervals[i] != '\0') {
            tmp += intervals[i];
        } else {
            ss << tmp;
            ss >> nums[index];
            tmp = "";
            index++;
            ss.clear();
        }
    }
    Stack<Interval> s;
    for (int i = 0; i < index; i = i + 2) {
        Interval inter(nums[i], nums[i + 1]);
        if (s.isEmpty() || inter.start > s.getTop().end || inter.end < s.getTop().start) {
            s.push(inter);
        }
        else {
            if (inter.end >= s.getTop().start && inter.end <= s.getTop().end && inter.start <= s.getTop().start) {
                Interval a;
                s.pop(a);
                a.start = inter.start;
                s.push(a);
            }
            if (s.getTop().start <= inter.start && inter.start <= s.getTop().end && inter.end >= s.getTop().end) {
                Interval a;
                s.pop(a);
                a.end = inter.end;
                s.push(a);
            }
            if (s.getTop().start <= inter.end && s.getTop().start >= inter.start && s.getTop().end <= inter.end &&
                s.getTop().end >= inter.start) {
                Interval a;
                s.pop(a);
                a.end = inter.end;
                a.start = inter.start;
                s.push(a);
            }
        }
    }
    Stack<Interval> x;
    while(!s.isEmpty()){
        Interval a;
        s.pop(a);
        x.push(a);
    }
    cout<<"Joined subset: ";
    while (!x.isEmpty()) {
        cout << '(' << x.getTop().start << ", " << x.getTop().end << ") ";
        x.pop();
    }
    cout<<endl;
}
bool precedence(char in, char st){
    if((in == '+' || in == '-') && (st == '*' || st == '/')){
        return true;
    }
    else if((in == '+' || in == '-') && (st == '+' || st == '-')){
        return true;
    }
    else{
        return false;
    }
}
string infix2prefix(string expression) {
    string tmp = "";
    for(int i = expression.length()-1; i > -1; i--){
        tmp += expression[i];
    }
    Stack<char> s;
    string res = "";
    for(int i = 0; i < tmp.length(); i++){
        if(isdigit(tmp[i])){
            res += tmp[i];
        }
        else{
            if(s.isEmpty()){
                s.push(tmp[i]);
            }
            else if(tmp[i] == ')'){
                s.push(tmp[i]);
            }
            else if(tmp[i] == '('){
                char c;
                while(s.getTop() != ')'){
                    s.pop(c);
                    res += c;
                }
                s.pop();
            }
            else if(precedence(tmp[i],s.getTop())){
                while(precedence(tmp[i], s.getTop())){
                    char c;
                    s.pop(c);
                    res += c;
                }
                s.push(tmp[i]);
            }
            else{
                s.push(tmp[i]);
            }
        }
    }
    while(!s.isEmpty()){
        char c;
        s.pop(c);
        res += c;
    }
    tmp = "";
    for(int i = res.length()-1; i > -1; i--){
        tmp += res[i];
    }
    return "Prefix form of " + expression + " is " + tmp;
}

void evaluatePrefix(string expression) {
    string tmp = "";
    double result;
    for(int i = expression.length()-1; i > -1; i--){
        tmp += expression[i];
    }
    Stack<double> nums;
    for(int i = 0; i < tmp.length(); i++) {
        if (isdigit(tmp[i])) {
            nums.push(tmp[i]-48);
        }
        else{
            double n1,n2;
            nums.pop(n1);
            nums.pop(n2);
            if(tmp[i] == '+'){
                result = n1 + n2;
            }
            else if(tmp[i] == '-'){
                result = n1 - n2;
            }
            else if(tmp[i] == '*'){
                result = n1 * n2;
            }
            else{
                result = n1 / n2;
            }
            nums.push(result);
        }
    }
    cout<<"Result of "<<expression<<" is: "<<nums.getTop()<<endl;
}