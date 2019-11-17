//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/TSORT/

#include <iostream>
#include <fstream>
#include <set>

#define ull unsigned long long int

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    multiset<ull> num;
    int tmp, c;

    //ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\TSORT\\in.txt");

    cin >> c;

    while(c--){
        cin >> tmp;
        num.insert(tmp);
    }
    for(int el : num)
        cout << el << "\n";
    return 0;
}