//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/INVCNT/

#include <iostream>
#include <fstream>
#include <set>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <chrono>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ui n,t;
lli l,r;
ulli size, no, tmp;
unordered_map<int,ulli> arr;
vector<ui> elem;
set<ui> s;

int prev(int ind){
    return (ind & (ind + 1))-1;
}

ulli getSum(int ind){
    ulli res = 0;
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
            arr.clear();
            elem.clear();
            s.clear();

            cin >> n;
            //calculate maximum size
            size = pow(2, floor(log2(n)) + 1);

            //read elements and transform them

            for (ui i = 0; i < n; ++i) {
                cin >> tmp;
                elem.push_back(tmp);
                s.insert(tmp);
            }

            auto it_v = elem.begin();
            for (ui i = 0; i < n; ++i) {
                *it_v = distance(s.begin(), s.find(*it_v)) + 1;
                it_v++;
            }

            //calculate how many elements smaller than elem.at(n-TEST-i) have been seen yet and add that number to the number of
            //inversions.
            for (auto it = elem.rbegin(); it != elem.rend(); ++it) {
                tmp = getSum(*it - 1);
                no += tmp;
                l = *it;
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