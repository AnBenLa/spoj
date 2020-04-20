//
// Created by Mortiferum on 12.01.2020.
// https://www.spoj.com/problems/SCAVHUNT/

#include <iostream>
#include <fstream>
#include <map>

using namespace std;
typedef unsigned int ui;
typedef unsigned long long int ulli;


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\SCAVHUNT\\in.txt");
    ui n, m;
    string a,b;
    cin >> n;
    for(ui i = 0; i < n; ++i){
        map<string,string> words;
        map<string,bool> start;
        cin >> m;
        for(ui j = 0; j < m - 1; ++j){
            cin >> a >> b;
            words.insert({a,b});
            if(start.find(b) == start.end())
                start.insert({b, false});
            else
                start[b] = false;
            if(start.find(a) == start.end()){
                start.insert({a,true});
            } else {
                start[a] = false;
            }
        }
        string cur;
        for(auto w : start){
            if(w.second)
                cur = w.first;
        }
        cout << "Scenario #"<< i + 1 << ":\n";
        for(ui i = 0; i < m; ++i){
            cout << cur << "\n";
            if(i != m-1) {
                cur = words.find(cur)->second;
            }
        }
        cout << "\n";
    }
    return 0;
}