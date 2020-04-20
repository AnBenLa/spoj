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

struct node;

ui far_ind, far_cost;
node* nodes [50010]{nullptr};
ui dist [50010]{0};

struct node{
    ui index;
    char value;
    vector<node*> neighbours;
    bool visited = false;
};

bool dfs (pair<int,int> start, ui a, ui b){
    
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ui n, num, a, b, cost;
    scanf("%d",&n);
    char mat [101][101], tmp;

    while(n--){
        vector<pair<int,int>> cand;
        node* nodes [100001]{nullptr};
        scanf("%d %d",&a, &b);
        for(ui i = 0; i < a; ++i){
            for(ui j = 0; j < b; ++j){
                cin >> tmp;
                if(tmp == 'A')
                    cand.push_back({i,j});
                mat[i][j] = tmp;
                nodes[i*j + j] = new node {i*j + j, tmp};
            }
        }
        bool pos = false;
        for(auto c : cand){
            if(dfs(c,a,b)){
                pos = true;
                break;
            }
        }
    }
    return 0;
}