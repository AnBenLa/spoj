//
// Created by Mortiferum on 08.12.2019.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned short us;
typedef unsigned int ui;

struct vertex {
    int index;
    vector<us> adjacent_vertices;
    int visited = -1;
    ui low;
    ui depth;
    bool artic = false;
};

//adds an edge from u to v and an edge from v to u (indices start with 1)
void add_edge(vector<vertex> &graph, us u, us v) {
    graph[u - 1].adjacent_vertices.push_back(v);
    graph[v - 1].adjacent_vertices.push_back(u);
}

//tries to visit the vertex vert. If vert has'nt been visited yet visit the subtree using depthFirstSearch
//if the vertex vert has been visited there is a loop
void visit(vector<vertex> &graph, vertex &vert, vertex &father) {
    vert.visited = 1;
    int children = 0;
    for (auto const &i : vert.adjacent_vertices) {
        vertex& child = graph[i - 1];
        if (child.visited == -1 && child.index != father.index) {
            children++;
            child.depth = vert.depth + 1;
            child.low = vert.depth + 1;

            visit(graph, child, vert);

            vert.low = min(vert.low, child.low);

            if(vert.depth > 0 && child.low >= vert.depth){
                vert.artic = true;
            }

        } else if(child.index != father.index){
            vert.low = min(vert.low, child.depth);
        }
    }
    if(vert.depth == 0 && children > 1){
        vert.artic = true;
    }
    vert.visited = 2;
}


void depthFirstSearch(vector<vertex> &graph) {
    for (auto &i : graph) {
        if (i.visited == -1) {
            i.depth = 0;
            i.low = 0;
            visit(graph, i, i);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\SUBMERGE\\in.txt");

    ui n,m,u,v;

    while(true){
        cin >> n >> m;
        vector<vertex> graph;
        if(n == 0 && m == 0){
            break;
        }

        for(int i = 0; i < n; ++i){
            graph.push_back({i+1});
        }

        while(m--){
            cin >> u >> v;
            add_edge(graph, u, v);
        }

        depthFirstSearch(graph);
        int result = 0;
        for(auto const& vert : graph){
            if(vert.artic)
                result++;
        }
        cout << result << "\n";
    }
    return 0;
}
