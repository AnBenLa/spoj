//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/BYTESE2/

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <vector>

#define ull unsigned long long int

using namespace std;



int main(){
    int c;
    ifstream cin ("C:\\Users\\Anton\\CLionProjects\\spoj\\BYTESSE2\\in.txt");

    cin >> c;

    while(c--){
        int n ;
        cin >> n;
        vector<int> num_pres;
        while(n--){
            int entry, exit;
            cin >> entry >> exit;
            for(int i = entry; i <= exit; ++i){
                while(i >= num_pres.size())
                    num_pres.push_back(0);
                num_pres[i] += 1;
            }
        }
        int max = *max_element(num_pres.begin(), num_pres.end());
        cout << max << endl;
    }
    return 0;
}