//
// Created by Mortiferum on 12.01.2020.
// https://www.spoj.com/problems/POLQUERY/

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;
typedef unsigned int ui;
typedef unsigned long long int ulli;


struct edge;

struct node{
    bool visited = false;
    vector<edge*> edges;
};

node nodes [100001]{};

struct edge{
    ui a,b;
    bool visited = false;
};

void dfs(ui pos){
    nodes[pos].visited = true;
    for(auto e : nodes[pos].edges){
        if(!e->visited){
            if(e->a != pos && !nodes[e->a].visited)
                dfs(e->a);
            else if(!nodes[e->b].visited)
                dfs(e->b);
        }
    }
}

bool reach(ui a, ui b){
    dfs(a);
    return nodes[b].visited;
}

bool block_road(ui a, ui b,ui g_1,ui g_2){
    for(edge* e : nodes[g_1].edges){
        if(e->b == g_2 || e->a == g_2)
            e->visited = true;
    }
    return reach(a,b);
}

bool block_city(ui a, ui b,ui c){
    nodes[c].visited = true;
    return reach(a,b);
}

void reset(ui a){
    for(ui i = 0; i <= a; ++i){
        nodes[i].visited = false;
        for(auto e : nodes[i].edges){
            e->visited = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\POLQUERY\\in.txt");
    ui n, e, a, b, q,t, g_1, g_2, c, a_q, b_q;
    cin >> n >> e;
    while(e--){
        cin >> a >> b;
        edge* cur_edge = new edge{a,b};
        nodes[a].edges.push_back(cur_edge);
        nodes[b].edges.push_back(cur_edge);
    }
    cin >> q;
    while(q--){
        cin >> t;
        if(t == 1){
            cin >> a_q >> b_q >> g_1 >> g_2;
            if(block_road(a_q,b_q,g_1,g_2))
                cout << "da\n";
            else
                cout << "ne\n";
        } else {
            cin >> a_q >> b_q >> c;
            if(block_city(a_q,b_q,c))
                cout << "da\n";
            else
                cout << "ne\n";
        }
        reset(a);
    }
    return 0;
}