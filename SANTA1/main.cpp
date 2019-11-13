//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/SANTA1/

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <map>

#define ull unsigned long long int

using namespace std;


struct reindeer{
    string name;
    ull sen;
    ull prod;
};

bool operator < (reindeer const& a, reindeer const& b){
    if(a.sen > b.sen){
        return true;
    } else if(a.sen == b.sen){
        return a.prod > b.prod;
    }
    return false;
}

bool operator == (reindeer const& a, reindeer const& b){
    return a.name == b.name;
}

ostream& operator << (ostream& os, set<reindeer> const& rs){
    ull s_prod = 0;
    if(rs.size() < 2)
        return os << s_prod;
    for(auto it = rs.begin(); it != rs.end(); ++it){
        auto p = it;
        p = ++p;
        if(p != rs.end())
            s_prod += (it)->prod*(p)->prod;
    }
    return os << s_prod;
}

int main(){
    int c;
    char tmp;
    set<reindeer> rs;
    map<string, reindeer> rm;
    //ifstream cin ("C:\\Users\\Anton\\CLionProjects\\spoj\\SANTA1\\in.txt");

    cin >> c;

    while(c--){
        cin >> tmp;
        string name;
        if(tmp == 'A'){
            ull sen, prod;
            cin >> name >> sen >> prod;
            reindeer new_r{name, sen, prod};
            rs.insert(new_r);
            rm.insert(pair<string,reindeer>(name, new_r));
        } else if(tmp == 'R'){
            cin >> name;
            rs.erase(rm[name]);
        }
        if(c > 0)
            cout << rs << endl;
        else
            cout << rs;
    }
    return 0;
}