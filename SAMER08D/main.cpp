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

ui memo[1010][1010]{0}, seq[1010][1010]{0};

ui long_subs(string& a, string& b, ui k){
    int n = a.size(), m = b.size();
    a = "0" + a; b = "0" + b;
    for(int i = 0; i <= n; ++i){
        for(int j = 0; j <= m; ++j){
            if(i == 0 || j == 0) {
                memo[i][j] = 0;
            } else {
                memo[i][j] = max(memo[i - 1][j], memo[i][j - 1]);
                if (a[i] == b[j]) {
                    seq[i][j] = seq[i-1][j-1] + 1;
                }
                if(seq[i][j] >= k){
                    for(ui m = k; m <= seq[i][j]; m++)
                        memo[i][j] = max(memo[i][j], memo[i-m][j-m] + m);
                }
            }
        }
    }
    return memo[n][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\SAMER08D\\in.txt");
    ui k;
    cin >> k;
    while(k != 0){
        string a,b;
        cin >> a >> b;
        cout << long_subs(a,b,k) << "\n";
        cin >> k;
        for(ui i = 0; i < a.size(); ++i)
            for(ui j = 0; j < b.size(); ++j) {
                memo[i][j] = 0;
                seq[i][j] = 0;
            }
    }
    return 0;
}
