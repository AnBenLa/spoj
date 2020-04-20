//
// Created by Mortiferum on 12.01.2020.
// https://www.spoj.com/problems/ALLIZWEL/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
typedef unsigned int ui;
typedef unsigned long long int ulli;

char tmp, mat[101][101] {'0'}, word [10] = {'A','L','L','I','Z','Z','W','E','L','L'};
bool visited[101][101], found;

void find(pair<int,int> pos, int ind){
    if(found)
        return;
    int a = pos.first, b = pos.second;
    visited[a][b] = true;
    vector<pair<int,int>> poss = {{a + 1, b},{a - 1, b},{a + 1, b - 1},{a + 1, b + 1}, {a - 1, b + 1}, {a - 1, b - 1},{a,b+1},{a, b- 1}};
    for(auto p : poss){
        if(p.first >= 0 && p.first <= 100 && p.second >= 0 && p.second <= 100){
            if(mat[p.first][p.second] == word[ind + 1] && !visited[p.first][p.second]){
                if(ind + 1 == 9) {
                    found = true;
                    return;
                } else {
                    find(p,ind + 1);
                }
            }
        }
    }
    visited[a][b] = false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\ALLIZWEL\\in.txt");
    ui n, num, a, b;
    vector<pair<int,int>> cand;
    cin >> n;

    while(n--){
        cin >> a >> b;
        for(ui i = 0; i < a; ++i)
            for(ui j = 0; j < b; ++j){
                cin >> tmp;
                if(tmp == 'A')
                    cand.emplace_back(pair<int,int>{i,j});
                mat[i][j] = tmp;
                visited[i][j] = false;
            }
        found = false;
        for(auto c : cand) {
            find(c, 0);
            if(found)
                break;
        }
        if(found)
            cout << "YES\n";
        else
            cout << "NO\n";
        for(ui i = 0; i < a; ++i)
            for(ui j = 0; j < b; ++j) {
                mat[i][j] = '0';
                visited[i][j] = false;
            }
        cand.clear();
    }
    return 0;
}