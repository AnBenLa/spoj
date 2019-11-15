//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/HOMO/

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <map>

using namespace std;



int main(){
    int c, homo_num = 0;
    set<int> val_set;
    map<int, int> val_occ;
    //ifstream cin ("C:\\Users\\Anton\\CLionProjects\\spoj\\HOMO\\in.txt");

    cin >> c;

    while(c--){
        string op;
        int val;
        bool hetero, homo;
        cin >> op >> val;
        if(op == "insert"){
            val_set.insert(val);
            val_occ[val] += 1;
            if(val_occ[val] == 2){
                homo_num += 1;
            }
        }else if(op == "delete"){
            if(val_occ.find(val) != val_occ.end()){
                if(val_occ[val] == 2){
                    homo_num -= 1;
                }
                if(val_occ[val] > 0) {
                    val_occ[val] = val_occ[val] - 1;
                }
                if(val_occ[val] == 0)
                    val_set.erase(val);
            }
        }

        hetero = val_set.size() > 1;
        homo = homo_num > 0;

        if(homo && hetero)
            cout << "both" << endl;
        if(homo && !hetero)
            cout << "homo" << endl;
        if(!homo && hetero)
            cout << "hetero" << endl;
        if(!homo && !hetero)
            cout << "neither" << endl;
    }


    return 0;
}