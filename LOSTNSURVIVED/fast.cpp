//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/LOSTNSURVIVED/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

unsigned int n,q,a,b,k = 0,root,root_2;
int tmp;
unordered_map<unsigned int, int> pers_m;
vector<unsigned int> passed_notes;

struct Cmp
{
    bool operator ()(pair<unsigned int,int> const& a, pair<unsigned int,int> const& b){
        if(a.second == b.second)
            return a.first < b.first;
        else
            return a.second < b.second;
    }
};

set<pair<unsigned int,int>, Cmp> pers_r;

int find_root(unsigned int b){
    passed_notes.clear();
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;

    while(q--){
        cin >> a >> b;
        if(pers_m.find(a) == pers_m.end() && pers_m.find(b) == pers_m.end()){
            //if a and b dont exists yet add them and set a as root of b
            root = a;
            pers_m[root] = -2;
            pers_m[b] = root;
            pers_r.insert(pair<unsigned int,int>(root,pers_m[root]));
            k += 2;
        } else if(pers_m.find(a) == pers_m.end()){
            //if b exists set the root of a to b
            root = find_root(b);
            pers_m[a] = root;
            pers_r.erase(pair<unsigned int,int>(root,pers_m[root]));
            pers_m[root] -= 1;
            pers_r.insert(pair<unsigned int,int>(root,pers_m[root]));
            k += 1;
        } else if(pers_m.find(b) == pers_m.end()){
            //if a exists set the root of b to a
            root = find_root(a);
            pers_m[b] = root;
            pers_r.erase(pair<unsigned int,int>(root,pers_m[root]));
            pers_m[root] -= 1;
            pers_r.insert(pair<unsigned int,int>(root,pers_m[root]));
            k += 1;
        } else {
            //if both exists check if they have the same root
            root = find_root(a);
            root_2 = find_root(b);
            pers_r.erase(pair<unsigned int,int>(root,pers_m[root]));
            //if the roots are different merge the two trees
            if(root != root_2){
                pers_r.erase(pair<unsigned int,int>(root_2,pers_m[root_2]));
                tmp = pers_m[root_2];
                pers_m[root_2] = root;
                pers_m[root] += tmp;
            }
            pers_r.insert(pair<unsigned int,int>(root,pers_m[root]));
        }
        if(k < n)
            cout << -pers_r.begin()->second - 1 << "\n";
        else if(-pers_r.begin()->second != n)
            cout << -pers_r.begin()->second + (--pers_r.end())->second << "\n";
        else
            cout << "0\n";
    }
    return 0;
}