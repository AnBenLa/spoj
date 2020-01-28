//https://www.spoj.com/problems/VONNY/
#include <iostream>
#include <vector>
#include <fstream>

using  namespace std;

int pos;

void find_all_pos(vector<vector<int>>& field, int a, int b){
    bool solution = true;

    for(int i = 0; i < field.size(); ++i) {
        for (int k = 0; k < field.at(i).size(); ++k) {
            if (field.at(i).at(k) != -1) {
                solution = false;
                break;
            }
        }
        if(!solution)
            break;
    }

    if(solution){
        pos += 1;
        return;
    }

    vector<pair<pair<int,int>,pair<int,int>>> opt;

    for(int i = 0; i < field.size(); ++i){
        for(int j = 0; j < field.at(i).size(); ++j){
            if(j + 1 < field.at(i).size() && ((field.at(i).at(j) == a && field.at(i).at(j+1) == b) || (field.at(i).at(j) == b && field.at(i).at(j+1) == a))){
                opt.push_back(pair<pair<int,int>, pair<int,int>>(pair<int,int>(i,j), pair<int,int>(i,j+1)));
            }
            if(i + 1 < field.size() && ((field.at(i).at(j) == a && field.at(i + 1).at(j) == b) || (field.at(i).at(j) == b && field.at(i + 1).at(j) == a))){
                opt.push_back(pair<pair<int,int>, pair<int,int>>(pair<int,int>(i,j), pair<int,int>(i+1,j)));
            }
        }
    }

    for(auto o : opt){
        int tmp_a = field.at(o.first.first).at(o.first.second);
        int tmp_b = field.at(o.second.first).at(o.second.second);
        field.at(o.first.first).at(o.first.second) = -1;
        field.at(o.second.first).at(o.second.second) = -1;
        int a_new = a, b_new = b + 1;
        if(b + 1 > 6) {
            b_new = a + 1;
            a_new = a + 1;
        }

        find_all_pos(field, a_new, b_new);
        field.at(o.first.first).at(o.first.second) = tmp_a;
        field.at(o.second.first).at(o.second.second) = tmp_b;
    }
}

int main() {
    int cases, tmp;
    ifstream inFile ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\224\\in.txt");

    inFile >> cases;

    for(int i = 0; i < cases; ++i){
        pos = 0;
        vector<vector<int>> field;
        for(int j = 0; j < 7; ++j){
            vector<int> row;
            for(int k = 0; k < 8; ++k){
                inFile >> tmp;
                row.push_back(tmp);
            }
            field.push_back(row);
        }
        vector<pair<int,int>> blocks;
        find_all_pos(field,0,0);
        cout << pos << endl;
    }
    return 0;
}