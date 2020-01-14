//
// Created by Mortiferum on 12.01.2020.
//

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef unsigned int ui;

ui n,m,coins[5],memo[5][100000];

int buildTable(int change, int n){
    for(int i = 0; i < n; ++i)
        memo[i][0] = 0;
    for(int j = 0; j <= change; ++j)
        memo[0][j] = (j % coins[0]) ? 9999999 : j/coins[0];
    for(int j = 1; j <= change; j++){
        for(int i = 1; i < n; ++i){
            if(j < coins[i])
                memo[i][j] = memo[i-1][j];
            else
                memo[i][j] = min(memo[i-1][j], memo[i][j-coins[i]] + 1);
        }
    }
    return memo[n-1][change];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\NOCHANGE\\int.txt");
    cin >> n >> m;
    for(ui i = 0; i < m; ++i){
        cin >> coins[i];
        if(i > 0)
            coins[i] += coins[i-1];
    }
    int coins_needed = buildTable(n, m);
    if(coins_needed != 9999999)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}
