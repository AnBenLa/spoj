//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/TSORT/

#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <unordered_map>
#include <chrono>

using namespace std;

bool operator < (pair<int,int> const& a, pair<int,int> const& b){
    return a.second > b.second;
}

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
    auto start = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,q,a,b,root,max,min;
    unordered_map<int, int> pers;
    set<pair<int,int>> roots;

    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\LOSTNSURVIVED\\in.txt");

    cin >> n >> q;

    while(q--){
        cin >> a >> b;
        if(pers.find(a) == pers.end() && pers.find(b) == pers.end()){
            root = a;
            pers[root] = -2;
            pers[b] = a;
        } else if(pers.find(a) == pers.end()){
            pers[a] = b;
            root = find_root(pers, b);
            roots.erase(pair<int,int>(root, pers[root]));
            pers[root] -= 1;
        } else if(pers.find(b) == pers.end()){
            pers[b] = a;
            root = find_root(pers,a);
            roots.erase(pair<int,int>(root, pers[root]));
            pers[root] -= 1;
        } else {
            root = find_root(pers,a);
            int root_2 = find_root(pers,b);
            if(root != root_2){
                int tmp = pers[root_2];
                pers[root_2] = root;
                roots.erase(pair<int,int>(root, pers[root]));
                pers[root] += tmp;
                roots.erase(pair<int,int>(root_2, tmp));
            }
        }
        roots.insert(pair<int,int>(root,pers[root]));
        if(roots.size() > 1) {
            auto last = roots.end();
            last--;
            min = -last->second;
            max = -roots.begin()->second;
            cout << max - min << "\n";
        } else if(roots.size() == 1){
            max = -roots.begin()->second;
            cout << max - 1 << "\n";
        }
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}