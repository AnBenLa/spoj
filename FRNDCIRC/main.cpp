//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/FRNDCIRC/

#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

int find_root(unordered_map<int,int>& a, int b){
    vector<int> passed_notes;
    while(a[b] > 0){
        passed_notes.push_back(b);
        b = a[b];
    }
    for(auto passed : passed_notes){
        a[passed] = b;
    }
    return b;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int c,r,root;
    string p1, p2;

    unordered_map<int, int> pers;
    unordered_map<string, int> pers_ind;

    //ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\FRNDCIRC\\in.txt");

    cin >> c;

    while(c--) {
        pers.clear();
        pers_ind.clear();
        cin >> r;
        int i = 1;
        while(r--){
            cin >> p1 >> p2;
            if(pers_ind.find(p1) == pers_ind.end() && pers_ind.find(p2) == pers_ind.end()) {
                pers_ind[p1] = i;
                i += 1;
                pers_ind[p2] = i;
                i += 1;
                pers[pers_ind[p1]] = -2;
                pers[pers_ind[p2]] = pers_ind[p1];
                root = pers_ind[p1];
            } else if(pers_ind.find(p1) == pers_ind.end()){
                pers_ind[p1] = i;
                i += 1;
                pers[pers_ind[p1]] = pers_ind[p2];
                root = find_root(pers, pers_ind[p2]);
                pers[root] -= 1;
            } else if(pers_ind.find(p2) == pers_ind.end()){
                pers_ind[p2] = i;
                i += 1;
                pers[pers_ind[p2]] = pers_ind[p1];
                root = find_root(pers, pers_ind[p1]);
                pers[root] -= 1;
            } else {
                root = find_root(pers, pers_ind[p1]);
                int u = find_root(pers, pers_ind[p2]);
                if(u != root) {
                    int tmp = pers[u];
                    pers[u] = root;
                    pers[root] += tmp;
                }
            }
            cout << -pers[root] << "\n";
        }
    }
    return 0;
}