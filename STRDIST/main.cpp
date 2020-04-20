//
// Created by Mortiferum on 12.01.2020.
//

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef unsigned int ui;
typedef  unsigned short us;

ui memory[2010][2010];
us num;

int distance(string const& a, string const& b){
    ui n = a.size(), m = b.size();
    for(ui i = 0; i <= n; ++i)
        memory[i][0] = i;
    for(ui i = 0; i <= m; ++i)
        memory[0][i] = i;
    for(ui i = 1; i <= n; ++i){
        for(ui j = 1; j <= m; ++j){
            if(a[i-1] == b[j-1])
                memory[i][j] = memory[i-1][j-1];
            else
                memory[i][j] = 1 + min(min(memory[i-1][j], memory[i][j-1]), memory[i-1][j-1]);
        }
    }
    return memory[n][m];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\EDIST\\in.txt");
    string a,b;
    cin >> num;
    while(num--){
        cin >> a >> b;
        cout << distance(a,b) << "\n";
        for(ui i = 0; i < a.size(); ++i)
            for(ui j = 0; j < b.size(); ++j)
                memory[i][j] = 0;
    }
    return 0;
}
