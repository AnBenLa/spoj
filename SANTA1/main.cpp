//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/SANTA1/

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <map>
#include <chrono>

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
    auto start = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    char tmp;
    string name;
    ull c,sen, prod, tot_prod = 0;
    set<reindeer> rs;
    map<string, reindeer> rm;

    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\SANTA1\\in.txt");

    cin >> c;

    while(c--){
        cin >> tmp;
        if(tmp == 'A'){
            cin >> name >> sen >> prod;
            reindeer new_r{name, sen, prod};
            rs.insert(new_r);
            auto ir = rs.find(new_r);
            auto irp = ir;
            auto irb = ir;
            auto end = rs.end();
            end--;
            if(ir == rs.begin()){
                irb++;
                if(irb != rs.end()){
                    tot_prod += ir->prod*irb->prod;
                }
                else{
                    tot_prod = 0;
                }
            }else if(ir == end){
                irp--;
                if(ir != rs.begin()){
                    tot_prod += ir->prod*irp->prod;
                }
            } else {
                irb++;
                irp--;
                tot_prod -= irp->prod*irb->prod;
                tot_prod += irp->prod*ir->prod + irb->prod*ir->prod;
            }
            rm.insert(pair<string,reindeer>(name, new_r));
        } else if(tmp == 'R'){
            cin >> name;
            reindeer rem_re = rm[name];
            auto ir = rs.find(rem_re);
            auto irp = ir;
            auto irb = ir;
            auto end = rs.end();
            end--;
            if(ir == rs.begin()){
                irb++;
                if(irb != rs.end()){
                    tot_prod -= ir->prod*irb->prod;
                }
                else{
                    tot_prod = 0;
                }
            }else if(ir == end){
                irp--;
                if(ir != rs.begin()){
                    tot_prod -= ir->prod*irp->prod;
                }
            } else {
                irb++;
                irp--;
                tot_prod += irp->prod*irb->prod;
                tot_prod -= irp->prod*ir->prod + irb->prod*ir->prod;
            }
            rs.erase(rem_re);

        }
        if(c > 0)
            cout << tot_prod << "\n";
        else
            cout << tot_prod;
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "\nElapsed time: " << elapsed.count() << " s\n";
    return 0;
}