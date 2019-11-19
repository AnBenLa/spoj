//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/CHAIN/

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#define ui unsigned int

using namespace std;

ui t,n,k,a,x,y,r,r_2,err;
vector<ui> passed_notes;
map<ui,ui> rel;
map<ui,ui> eats;

int find_root(ui b){
    passed_notes.clear();
    //finding root node of b in pers
    while(rel[b] != 0){
        passed_notes.push_back(b);
        b = rel[b];
    }
    //path compression
    for(auto passed : passed_notes){
        rel[passed] = b;
    }
    return b;
}

bool contradiction(ui x, ui y){
    ui ry = find_root(y);
    ui rx = find_root(x);
    ui ryn = find_root(eats[ry]);
    ui rxn = find_root(eats[rx]);
    ui rynn = find_root(eats[ryn]);
    ui rxnn = find_root(eats[rxn]);
    return (ry == rx || rx == ryn || rxnn == ry || rynn == rxn);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\CHAIN\\in.txt");

    cin >> t;

    while(t--) {
        rel.clear();
        eats.clear();
        err = 0;
        cin >> n >> k;
        for(int i = 1; i <= n; ++i){
            rel[i] = 0;
        }
        while (k--) {
            cin >> a >> x >> y;
            if (x > n || y > n) {
                err += 1;
            } else {
                if (a == 1) {
                    if(contradiction(x,y)) {
                        err += 1;
                    } else {
                        if (rel[x] == 0 && rel[y] == 0) {
                            if(x != y) {
                                rel[y] = x;
                                rel[x] = 0;
                            }
                        } else if (rel[x] == 0) {
                            r = find_root(y);
                            rel[x] = r;
                        } else if (rel[y] == 0) {
                            r = find_root(x);
                            rel[y] = r;
                        } else {
                            r = find_root(x);
                            r_2 = find_root(y);
                            if(contradiction(x,y)){
                                err += 1;
                            } else {
                                rel[r_2] = r;
                            }
                        }
                    }
                } else {
                    if(x == y){
                        err += 1;
                    } else {
                        if(contradiction(x,y)){
                            err+=1;
                        } else {
                            eats[find_root(x)] = find_root(y);
                        }
                    }
                }
            }
        }
        cout << err << "\n";
    }
    return 0;
}