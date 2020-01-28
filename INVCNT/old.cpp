//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/INVCNT/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <cstring>
#include <chrono>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ui n,t;
lli l,r;
ulli size, no, tmp;
ulli arr[524288];
vector<ui> elem;
set<ui> s;

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

void increment(){
    while(l < size){
        arr[l] += r;
        l |= l+1;
    }
}

int main(){
    auto start = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    for(int k = 0; k < 100; ++k) {
        ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\INVCNT\\in.txt");

        cin >> t;
        while (t--) {
            //reset values
            no = 0;
            memset(arr, 0, sizeof(arr));
            elem.clear();
            s.clear();

            cin >> n;
            //calculate maximum size
            size = pow(2, floor(log2(n)) + 1);

            //read elements and transform them
            for (int i = 0; i < n; ++i) {
                cin >> tmp;
                elem.push_back(tmp);
                s.insert(tmp);
            }

            for (int i = 0; i < n; ++i) {
                elem.at(i) = distance(s.begin(), s.find(elem.at(i))) + 1;
            }

            //calculate how many elements smaller than elem.at(n-TEST-i) have been seen yet and add that number to the number of
            //inversions.
            for (int i = 0; i < n; ++i) {
                tmp = getSum(elem.at(n - 1 - i) - 1);
                no += tmp;
                l = elem.at(n - 1 - i);
                r = 1;
                increment();
            }

            cout << no << "\n";
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "\nElapsed time: " << elapsed.count() << " s\n";
    return 0;
}