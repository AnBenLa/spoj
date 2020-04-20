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

vector<ui> graph[200010],c_graph[200010];
stack<ui> st;
ui scc[200010]{0}, in_deg[200010]{0};
bool visited [200010]{false};

void dfs(ui i){
    visited[i] = true;
    for(auto adj : graph[i]){
        if(!visited[adj])
            dfs(adj);
    }
    st.push(i);
}

void dfs_c(ui i, ui cur_scc){
    visited[i] = false;
    scc[i] = cur_scc;
    for(auto adj : c_graph[i]){
        if(visited[adj])
            dfs_c(adj, cur_scc);
    }
    st.push(i);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\CAPCITY\\in.txt");

    ui n, m, u, v;
    cin >> n >> m;
    while(m--){
        cin >> u >> v;
        graph[u].push_back(v);
        c_graph[v].push_back(u);
    }
    for(ui i = 1; i <= n; ++i){
        if(!visited[i])
            dfs(i);
    }
    ui cur_scc = 1;

    //find sccs and save to which scc a node belongs
    while(!st.empty()){
        if(visited[st.top()]) {
            dfs_c(st.top(), cur_scc);
            cur_scc++;
        }
        st.pop();
    }

    //calculate the in degree for each scc
    for(ui i = 1; i <= n; ++i){
        for(auto adj : graph[i]){
            if(scc[i] != scc[adj]){
                in_deg[scc[i]]++;
            }
        }
    }
    //calculate how many sccs hav an in_degree of 0
    ui num = 0;
    for(ui i = 1; i < cur_scc; ++i){
        if(in_deg[i] == 0)
            num++;
    }
    if(num > 1)
        cout << "0\n";
    else{
        set<ui> sol;
        for(ui i = 1; i <= n; ++i){
            if(in_deg[scc[i]] == 0)
                sol.insert(i);
        }
        cout << sol.size() << "\n";
        for(auto n : sol)
            cout << n << " ";
        cout << "\n";
    }

    return 0;
}
