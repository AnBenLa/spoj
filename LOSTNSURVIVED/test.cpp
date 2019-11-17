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

int n,q,a,b,root,tmp;
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

    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\LOSTNSURVIVED\\in.txt");

    cin >> n >> q;

    for(int i = 1; i <= n; ++i){
        pers_m[i] = -1;
        pers_r.insert(pair<int,int>(i,-1));
    }

    while(q--){
        cin >> a >> b;
        if(pers_m[a] == -1 && pers_m[b] == -1){
            //if a and b dont exists yet add them and set a as root of b
            root = a;
            pers_m[root] = -2;
            pers_r.erase(pair<int,int>(a,-1));
            pers_r.erase(pair<int,int>(b,-1));
            pers_m[b] = a;
            pers_r.insert(pair<int,int>(root,pers_m[root]));
        } else if(pers_m[a] == 0){
            //if b exists set the root of a to b
            pers_r.erase(pair<int,int>(a,-1));
            pers_m[a] = b;
            root = find_root(b);
            pers_r.erase(pair<int,int>(root,pers_m[root]));
            pers_m[root] -= 1;
            pers_r.insert(pair<int,int>(root,pers_m[root]));
        } else if(pers_m[b] == 0){
            //if a exists set the root of b to a
            pers_r.erase(pair<int,int>(b,-1));
            pers_m[b] = a;
            root = find_root(a);
            pers_r.erase(pair<int,int>(root,pers_m[root]));
            pers_m[root] -= 1;
            pers_r.insert(pair<int,int>(root,pers_m[root]));
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
        if(pers_r.size() > 1)
            cout << -pers_r.begin()->second + (--pers_r.end())->second << "\n";
        else
            cout << "0\n";
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}