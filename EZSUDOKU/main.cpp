//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/EZSUDOKU/

#include <iostream>
#include <vector>
#include <fstream>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ui t, tmp;
ui sod[8][8];
vector<pair<ui,ui>> zeros;
bool solution, valid;

void is_valid(){
    valid = true;
    for(int i = 0; i < 8; ++i){
        bool found_r[]  = {false,false,false,false,false,false,false,false,false};
        bool found_c[]  = {false,false,false,false,false,false,false,false,false};
        for(int k = 0; k < 8; ++k){
            if(found_r[sod[k][i]]) {
                valid = false;
                return;
            } else {
                found_r[sod[k][i]] = true;
            }
            if(found_c[sod[i][k]]) {
                valid = false;
                return;
            } else {
                found_c[sod[i][k]] = true;
            }
        }

        ui square[] = {0,0,0,0,0,0,0,0,0};
        for(int i = 0; i < 4; ++i){
            for(int k = 0; k < 4; ++k){
                if(square[sod[i][k]] == 2) {
                    valid = false;
                    return;
                }
                square[sod[i][k]] += 1;
            }
        }

        ui square_2[] = {0,0,0,0,0,0,0,0,0};
        for(int i = 4; i < 8; ++i){
            for(int k = 0; k < 4; ++k){
                if(square_2[sod[i][k]] == 2) {
                    valid = false;
                    return;
                }
                square_2[sod[i][k]] += 1;
            }
        }

        ui square_3 [] = {0,0,0,0,0,0,0,0,0};
        for(int i = 0; i < 4; ++i){
            for(int k = 4; k < 8; ++k){
                if(square_3[sod[i][k]] == 2) {
                    valid = false;
                    return;
                }
                square_3[sod[i][k]] += 1;
            }
        }

        ui square_4 []= {0,0,0,0,0,0,0,0,0};
        for(int i = 4; i < 8; ++i){
            for(int k = 4; k < 8; ++k){
                if(square_4[sod[i][k]] == 2) {
                    valid = false;
                    return;
                }
                square_4[sod[i][k]] += 1;
            }
        }
    }
}

void find_solution(ui ind_zero){
    if(solution)
        return;
    if(zeros.size() == ind_zero){
        is_valid();
        if(valid){
            solution = true;
            return;
        }
        return;
    }

    pair<ui,ui> pos = zeros[ind_zero];
    for(ui v = 1; v < 9; ++v){
        sod[pos.first][pos.second] = v;
        find_solution(ind_zero + 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\EZSUDOKU\\in.txt");

    cin >> t;
    for (ui m = 1; m <= t; ++m) {
        solution = false;
        zeros.clear();
        for(int i = 0; i < 8; ++i){
            for(int k = 0; k < 8; ++k){
                cin >> tmp;
                if(tmp == 0){
                    zeros.push_back(pair<ui,ui>(i,k));
                }
                sod[i][k] = tmp;
            }
        }

        find_solution(0);
        if(solution){
            cout << "DCEPC501 case #" << m << ": YES\n";
            for(int i = 0; i < 8; ++i){
                for(int k= 0; k < 8; ++k){
                    cout << sod[i][k] << " ";
                    if(k == 7)
                        cout << "\n";
                }
            }
        } else {
            cout << "DCEPC501 case #" << m << ": NO\n";
        }
    }
    return 0;
}