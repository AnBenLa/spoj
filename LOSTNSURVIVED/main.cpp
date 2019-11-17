//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/LOSTNSURVIVED/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <chrono>

using namespace std;

pair<int,int> mi = pair<int,int>(0,1), ma = pair<int,int>(0,1);

int n,q,a,b,root,tmp,k = 0;
unordered_map<int, int> pers_m;

struct Cmp
{
    bool operator ()(pair<int,int> const& a, pair<int,int> const& b){
        if(a.second == b.second)
            return a.first < b.first;
        else
            return a.second < b.second;
    }
};

set<pair<int,int>, Cmp> pers_r;

int find_root(int b){
    vector<int> passed_notes;
    //finding root node of b in pers
    while(pers_m[b] > 0){
        passed_notes.push_back(b);
        b = pers_m[b];
    }
    //path compression
    for(auto passed : passed_notes){
        pers_m[passed] = b;
    }
    return b;
}


int main(){
    auto start = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\LOSTNSURVIVED\\in-3.txt");

    cin >> n >> q;
    int i = 0;
    while(q--){
        //cin >> a >> b;
        a = i;
        ++i;
        b = i;
        ++i;
        if(pers_m.find(a) == pers_m.end() && pers_m.find(b) == pers_m.end()){
            //if a and b dont exists yet add them and set a as root of b
            root = a;
            pers_m[root] = -2;
            pers_m[b] = a;
            pers_r.insert(pair<int,int>(root,pers_m[root]));
            k += 2;
        } else if(pers_m.find(a) == pers_m.end()){
            //if b exists set the root of a to b
            pers_m[a] = b;
            root = find_root(b);
            pers_r.erase(pair<int,int>(root,pers_m[root]));
            pers_m[root] -= 1;
            pers_r.insert(pair<int,int>(root,pers_m[root]));
            k += 1;
        } else if(pers_m.find(b) == pers_m.end()){
            //if a exists set the root of b to a
            pers_m[b] = a;
            root = find_root(a);
            pers_r.erase(pair<int,int>(root,pers_m[root]));
            pers_m[root] -= 1;
            pers_r.insert(pair<int,int>(root,pers_m[root]));
            k += 1;
        } else {
            //if both exists check if they have the same root
            root = find_root(a);
            int root_2 = find_root(b);
            pers_r.erase(pair<int,int>(root,pers_m[root]));
            //if the roots are different merge the two trees
            if(root != root_2){
                pers_r.erase(pair<int,int>(root_2,pers_m[root_2]));
                tmp = pers_m[root_2];
                pers_m[root_2] = root;
                pers_m[root] += tmp;
            }
            pers_r.insert(pair<int,int>(root,pers_m[root]));
        }
        if(k < n)
            cout << -pers_r.begin()->second - 1 << "\n";
        else if(-pers_r.begin()->second != n)
            cout << -pers_r.begin()->second + (--pers_r.end())->second << "\n";
        else
            cout << "0\n";
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}