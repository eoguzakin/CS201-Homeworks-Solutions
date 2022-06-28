//
// Created by Asus on 1.04.2022.
//

#include <ctime>
#include <iostream>
using namespace std;
long alg1(long a, long long n, int p){
    if(p == 1) return 0;
    long long c = 1;
    for(long long i = 0; i < n; i++){
        c = (a * c) % p;
    }
    return c;
}
long long alg2(long long a, long long n, int p){
    if(p == 1) return 0;
    else if(n == 0 || a == 1) return 1;
    bool cycle = false;
    long long i = 0;
    long long tmp = 1;
    for(; i < n; i++){
        tmp *= a;
        if(tmp % p == 1){
            cycle = true;
            break;
        }
    }
    tmp = 1;
    if(cycle){
        for(long long j = 0; j < n%i; j++){
            tmp *= a;
        }
        return tmp % p;
    }
    else{
        return alg1(a,n,p);
    }
}
long long alg3(long a, long long n, int p){
    if(p == 1) return 0;
    else if(n == 1){
        return a % p;
    }
    long long y;
    if(n % 2 == 1){
        y = (a * alg3(a,(n-1)/2,p) * alg3(a,(n-1)/2,p)) % p;
    }
    else{
        y = (alg3(a,n/2,p) * alg3(a,n/2,p)) % p;
    }
    return y;
}
void measure(long long N, int P){
    double duration;
    clock_t startTime = clock();
    long long a1 = alg1(178912,N,P);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Execution took " << duration << " milliseconds." << endl;
    startTime = clock();
    long long a2 = alg2(178912,N,P);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Execution took " << duration << " milliseconds." << endl;
    startTime = clock();
    long long a3 = alg3(178912,N,P);
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Execution took " << duration << " milliseconds." << endl;
    cout<< a1 << " is alg1" << endl;
    cout<< a2 << " is alg2" << endl;
    cout<< a3 << " is alg3" << endl;
}
int main(){
    measure(4700000000,101);
    return 0;
}
