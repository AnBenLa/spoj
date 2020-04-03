//
// Created by Mortiferum on 08.12.2019.
//
#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>

using namespace std;
typedef unsigned short us;
typedef unsigned long long int ulli;
typedef unsigned long long ull;
typedef long long int lli;
typedef unsigned int ui;

ui n,m,a,b,q, roots, root, root_2;
int rel [100010];
vector<ui> passed_notes;

int find_root(int b){
    passed_notes.clear();
    //finding root node of b in pers
    while(rel[b] > 0){
        passed_notes.push_back(b);
        b = rel[b];
    }
    //path compression
    for(auto passed : passed_notes){
        rel[passed] = b;
    }
    return b;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin ("C:\\Users\\Elke\\Desktop\\Anton\\Competetive-Programming\\spoj\\SOCNETC\\in.txt");

    cin >> n >> m >> q;
    roots = n;
    string op;
    for(ui i = 1; i <= n; ++i){
        rel[i] = -1;
    }
    while(q--){
        cin >> op;
        if(op == "S"){
            cin >> a;
            if(rel[a] < 0)
                cout << -rel[a] << "\n";
            else
                cout << -rel[find_root(rel[a])] << "\n";
        } else if(op == "A"){
            cin >> a >> b;
            int r_a = find_root(a);
            int s_a = -rel[r_a];
            int r_b = find_root(b);
            int s_b = -rel[r_b];
            if(s_a + s_b <= m && r_a != r_b) {
                rel[r_a] = r_b;
                rel[r_b] = -(s_a + s_b);
            }
        } else {
            cin >> a >> b;
            if(find_root(a) == find_root(b))
                cout << "Yes\n";
            else
                cout << "No\n";
        }
    }
    return 0;
}