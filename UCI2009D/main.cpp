//https://www.spoj.com/problems/UCI2009D/
#include <iostream>
#include <vector>
#include <fstream>
#include <set>

using  namespace std;

set<vector<vector<bool>>> sol_set;

void digg(vector<vector<bool>>& field, pair<int,int> pos, int c_em){
    c_em += 1;
    field.at(pos.first).at(pos.second) = false;

    if(c_em == 8) {
        sol_set.insert(field);
        return;
    }

    vector<pair<int,int>> options;
    if(pos.second < field.at(pos.first).size() - 1){
        if(field.at(pos.first).at(pos.second + 1)) {
            options.push_back(pair<int,int>(pos.first, pos.second + 1));
        }
    }
    if(pos.second > 0){
        if(field.at(pos.first).at(pos.second - 1)) {
            options.push_back(pair<int,int>(pos.first, pos.second - 1));
        }
    }
    if(pos.first > 0){
        if(field.at(pos.first - 1).at(pos.second)) {
            options.push_back(pair<int,int>(pos.first - 1, pos.second));
        }
    }
    if(pos.first < field.size() - 1){
        if(field.at(pos.first + 1).at(pos.second)) {
            options.push_back(pair<int,int>(pos.first + 1, pos.second));
        }
    }

    for(auto option : options){
        digg(field, option, c_em);
        field.at(option.first).at(option.second) = true;
    }
}

int main() {
    int cases, dim;
    char tmp;

    //ifstream inFile ("C:\\Users\\Anton\\CLionProjects\\spoj\\4525\\in.txt");

    cin >> cases;

    for(int i = 0; i < cases; ++i) {
        vector<vector<bool>> field;
        cin >> dim;
        for(int j = 0; j < dim; ++j){
            vector<bool> row;
            for(int k = 0; k < dim; ++k){
                cin >> tmp;
                if(tmp == 'X'){
                    row.push_back(true);
                } else if(tmp == '.'){
                    row.push_back(false);
                }
            }
            field.push_back(row);
        }

        for(int j = 0; j < dim; ++j){
            for(int k = 0; k < dim; ++k){
                if(field.at(j).at(k)) {
                    digg(field, pair<int, int>(j, k), 0);
                    field.at(j).at(k) = true;
                }
            }
        }
        cout << sol_set.size() << endl;
        sol_set.clear();
    }

    return 0;
}