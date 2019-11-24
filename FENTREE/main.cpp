//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/FENTREE/

#include <iostream>
#include <fstream>
#include <cmath>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ui n,q;
lli sum,l,r;
ulli size;
lli arr[1050000];
char op;

lli prev(lli ind){
    return (ind & (ind + 1))-1;
}

lli getSum(lli ind){
    lli res = 0;
    while(ind >= 0){
        res += arr[ind];
        ind = prev(ind);
    }
    return res;
}

void solveQuery(){
    sum = getSum(r-1) - getSum(l-2);
}

void increment(){
    while(l < size){
        arr[l] += r;
        l |= l+1;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\FENTREE\\in.txt");

    cin >> n;

    size = pow(2,floor(log2(n)) + 1);

    for(ui i = 0; i < n; ++i){
        cin >> r;
        l = i;
        increment();
    }

    cin >> q;
    while(q--){
        cin >> op >> l >> r;
        if(op == 'q'){
            solveQuery();
            cout << sum << "\n";
        } else {
            l -= 1;
            increment();
        }
    }

    return 0;
}