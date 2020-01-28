//
// Created by Mortiferum on 08.12.2019.
// https://www.spoj.com/problems/PT07Y/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int subset_count;
bool loop;

struct vertex{
    int index;
    vector<int> adjacent_vertices;
    int visited = -1;
};

//adds an edge from u to v and an edge from v to u (indices start with TEST)
void add_edge(vector<vertex>& graph, int u , int v){
    graph[u - 1].adjacent_vertices.push_back(v);
    graph[v - 1].adjacent_vertices.push_back(u);
}

//tries to visit the vertex vert. If vert has'nt been visited yet visit the subtree using depthFirstSearch
//if the vertex vert has been visited there is a loop
void visit(vector<vertex>& graph, vertex& vert, vertex& father){
    if(loop)
        return;
    if(vert.visited == -1) {
        vert.visited = 1;
        for (auto const &i : vert.adjacent_vertices) {
            if(i != father.index) {
                visit(graph, graph[i - 1], vert);
            }
        }
        vert.visited = 2;
    } else {
        loop = true;
    }
}

void depthFirstSearch(vector<vertex>& graph){
       subset_count = 0;
       for(auto & i : graph){
           if(i.visited == -1){
               visit(graph,i, i);
               subset_count++;
               if(subset_count > 1)
                   return;
           }
       }

}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\PT07Y\\in.txt");
    int n,m;
    cin >> n >> m;
    if(m == n - 1){
        loop = false;
        vector<vertex> graph;
        int u, v;
        for(int i = 0; i < n; ++i){
            graph.push_back(vertex{i+1});
        }
        while(m--){
            cin >> u >> v;
            add_edge(graph, u, v);
        }
        depthFirstSearch(graph);
        if(subset_count == 1 && !loop){
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    } else {
        cout << "NO\n";
    }
    return 0;
}
