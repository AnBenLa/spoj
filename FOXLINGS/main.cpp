//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/FOXLINGS/

#include <iostream>
#include <vector>
//#include <fstream>
#include <map>
#include <unordered_map>
#define ui unsigned int

using namespace std;

ui n,m,a,b;
map<ui,ui> rel;
vector<ui> passed_notes;
ui roots, root, root_2;

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


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\FOXLINGS\\in.txt");

    cin >> n >> m;

    roots = n;

    while(m--){
        cin >> a >> b;
        if(rel.find(a) == rel.end() && rel.find(b) == rel.end()){
            //if a and b dont exists yet add them and set a as root of b
            rel[a] = 0;
            rel[b] = a;
            roots -= 1;
        } else if(rel.find(a) == rel.end()){
            //if b exists set the root of a to b
            root = find_root(b);
            rel[a] = root;
            roots -= 1;
        } else if(rel.find(b) == rel.end()){
            //if a exists set the root of b to a
            root = find_root(a);
            rel[b] = root;
            roots -= 1;
        } else {
            //if both exists check if they have the same root
            root = find_root(a);
            root_2 = find_root(b);
            //if the roots are different merge the two trees
            if(root != root_2){
                roots -= 1;
                rel[root_2] = root;
            }
        }
    }
    cout << roots << "\n";
    return 0;
}