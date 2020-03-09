//
// Created by Mortiferum on 12.01.2020.
// https://www.spoj.com/problems/BENEFACT/

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

struct edge{
    ui weight, start, dest;
};

struct node{
    ui index;
    vector<edge> edges;
    bool visited = false;
};

pair <int,int> find_far(int start){
    queue<int> q;
    q.push(start);
    ui max_ind = 0, cur_max = 0;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        if(!nodes[cur - 1]->visited) {
            for (auto e : nodes[cur - 1]->edges) {
                if(!nodes[e.dest - 1]->visited) {
                    q.push(e.dest);
                    dist[e.dest - 1] = dist[cur - 1] + e.weight;
                    if(dist[e.dest - 1] > cur_max) {
                        cur_max = dist[e.dest - 1];
                        max_ind = e.dest;
                    }
                }
            }
        }
        nodes[cur - 1]->visited = true;
    }
    return{cur_max, max_ind};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\BENEFACT\\in.txt");
    ui n, num, a, b, cost;
    scanf("%d",&n);

    while(n--){
        scanf("%d",&num);
        for(ui i = 0; i < num; ++i){
            nodes[i] = new node{i+1};
        }
        for(ui i = 0; i < num - 1; ++i) {
            scanf("%d %d %d", &a, &b, &cost);
            nodes[a-1]->edges.push_back({cost,a,b});
            nodes[b-1]->edges.push_back({cost,b,a});
        }
        pair<int,int> ans = find_far(1);
        for(ui i = 0; i < num; ++i){
            dist[i] = 0;
            nodes[i]->visited = false;
        }
        ans = find_far(ans.second);
        cout << ans.first << "\n";
        for(ui i = 0; i < num; ++i){
            delete nodes[i];
        }
    }
    return 0;
}