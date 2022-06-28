//
//  Oğuz Akın
//  22002893
#ifndef CS201_HW4_STACK_H
#define CS201_HW4_STACK_H

template <typename T> class Stack {
public:
    Stack() {
        top=-1;
    }
    bool push(T k){
        if(top != 24){
            top++;
            stack[top] = k;
            return true;
        }
        return false;
    }
    bool pop(){
        if(!isEmpty()){
            top--;
            return true;
        }
        return false;
    }
    bool pop(T &x){
        if(!isEmpty()){
            x = stack[top];
            top--;
            return true;
        }
        return false;
    }
    T getTop(){
        return stack[top];
    }
    bool isEmpty(){
        return top == -1;
    }
private:
    int top;
    T stack[25];
};


#endif //CS201_HW4_STACK_H
