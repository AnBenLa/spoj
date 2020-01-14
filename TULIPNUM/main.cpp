//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/TULIPNUM/

#include <iostream>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <cmath>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ui n,q,t;
lli sum,l,r;
ulli size;
vector<unordered_set<ulli>> arr;
unordered_set<ulli> res;

unordered_set<ulli> operator += (unordered_set<ulli>& a, unordered_set<ulli> const& b){
    for(auto elem : b){
        a.insert(elem);
    }
    return a;
}

unordered_set<ulli> operator += (unordered_set<ulli>& a, lli b){
    a.insert(b);
    return a;
}

ulli operator - (unordered_set<ulli> const& a, unordered_set<ulli> const& b){
    ulli s = 0;
    for(auto elem : a){
        if(b.find(elem) == b.end()){
            s += 1;
        }
    }
    return s;
}

lli prev(lli ind){
    return (ind & (ind + 1))-1;
}

unordered_set<ulli> getSum(lli ind){
    res.clear();
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

    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\TULIPNUM\\in.txt");

    cin >> t;
    while(t--) {
        arr.clear();
        cin >> n >> q;

        size = pow(2, floor(log2(n)) + 1);

        for(int i = 0; i < size; ++i){
            arr.push_back(unordered_set<ulli>{});
        }

        for (ui i = 0; i < n; ++i) {
            cin >> r;
            l = i;
            increment();
        }

        while (q--) {
            cin >> l >> r;
            solveQuery();
            cout << sum << "\n";
        }
    }
    return 0;
}