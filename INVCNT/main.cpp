//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/INVCNT/

#include <iostream>
//#include <fstream>
#include <set>
//#include <vector>
#include <cmath>
//#include <chrono>
#include <algorithm>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ui n,t,l;
ulli no, tmp;
ulli arr[200002];
ui elem[200002];
ui tmp_a[200002];
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
    while(l < n){
        arr[l] += 1;
        l |= l+1;
    }
}

ui find_v(ui a){
    ui start = 0, end = n;
    while(start <= end){
        ui mid = (start + end) >> 1;
        if(tmp_a[mid] == a)
            return mid;
        else if(tmp_a[mid] > a)
            end = mid - 1;
        else
            start = mid + 1;
    }
}

int main(){
    //auto start = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //for(int k = 0; k < 100; ++k) {
        //ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\INVCNT\\in.txt");

        cin >> t;
        while (t--) {
            //reset values
            no = 0;
            cin >> n;
            //read elements and transform them

            for (ui i = 0; i < n; ++i) {
                cin >> tmp;
                arr[i] = 0;
                elem[i] = tmp;
                tmp_a[i] = tmp;
            }

            sort(tmp_a, tmp_a + n);

            for (ui i = 0; i < n; ++i) {
                elem[i] = find_v(elem[i]);
            }

            //calculate how many elements smaller than elem.at(n-1-i) have been seen yet and add that number to the number of
            //inversions.
            for (auto i = 0; i < n; ++i) {
                no += getSum(elem[n - 1 - i] - 1);
                l = elem[n - 1 - i];
                increment();
            }
            cout << no << "\n";
        }
    //}
    //auto finish = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> elapsed = finish - start;
    //std::cout << "\nElapsed time: " << elapsed.count() << " s\n";

    return 0;
}