//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/LOSTNSURVIVED/

#include <iostream>
//#include <fstream>
#include <vector>
#include <set>
//#include <chrono>

using namespace std;

unsigned int father [100001];
unsigned int value [100001];
unsigned int n,q,a,b,root,root_2;
vector<unsigned int> passed_notes;
multiset<unsigned int> root_s;

int find_root(unsigned int b){
    passed_notes.clear();
    //finding root node of b in pers
    while(father[b] > 0){
        passed_notes.push_back(b);
        b = father[b];
    }
    //path compression
    for(auto passed : passed_notes){
        father[passed] = b;
    }
    return b;
}


int main(){
    //auto start = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\LOSTNSURVIVED\\in.txt");

    cin >> n >> q;

    for(int i = 1; i <= n; ++i){
        father[i] = 0;
        value[i] = 1;
        root_s.insert(1);
    }

    while(q--){
        cin >> a >> b;
        root = find_root(a);
        root_2 = find_root(b);
        root_s.erase(root_s.find(value[root]));
        if(root != root_2){
            root_s.erase(root_s.find(value[root_2]));
            father[root_2] = root;
            value[root] += value[root_2];
        }
        root_s.insert(value[root]);
        cout << *(--root_s.end()) - *root_s.begin() << "\n";
    }
    //auto finish = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double> elapsed = finish - start;
    //std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}