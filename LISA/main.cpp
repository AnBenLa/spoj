//
// Created by Mortiferum on 08.12.2019.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;
typedef unsigned short us;
typedef unsigned int ui;

ui dp[101][101]{0};
string exp;

int mcm(bool max){
    ui size = exp.size()/2;
    for(ui i = 0; i < size + 1; ++i)
        dp[i][i] = exp[2*i] - '0';
    for(ui i = 0; i < size; ++i){
        if(exp[2*i + 1] == '+')
            dp[i][i+1] = (exp[2*i] - '0') +  (exp[2*i+2] - '0');
        else
            dp[i][i+1] = (exp[2*i] - '0') *  (exp[2*i+2] - '0');
    }

    for(ui l = 1; l < size + 1; ++l){
        for(ui i = 0; i < size - l + 1; ++i){
            ui j = i + l;
            for(ui k = i; k < j; k++){
                ui l = dp[i][k];
                ui h = dp[k+1][j];
                ui m;
                if(exp[2*k + 1] == '+')
                    m = h + l;
                else
                    m = h * l;
                if(m > dp[i][j] && max)
                    dp[i][j] = m;
                else if(m < dp[i][j] && !max)
                    dp[i][j] = m;
            }
        }
    }
    return dp[0][size];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\LISA\\in.txt");
    ui k;
    cin >> k;
    while(k--){
        cin >> exp;
        cout << mcm(true) << " " << mcm(false) << "\n";
        for(ui i = 0; i < exp.size(); ++i){
            for(ui j = i; j < exp.size(); ++j){
                dp[i][j] = 0;
            }
        }
    }
    return 0;
}
