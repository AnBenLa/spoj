//
// Created by Mortiferum on 08.12.2019.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int subset_count;
bool error;

struct vertex {
    int index;
    vector<int> adjacent_vertices;
    int visited = -1;
    //-TEST for red and TEST for blue
    int color = 0;
};

//adds an edge from u to v and an edge from v to u (indices start with TEST)
void add_edge(vector<vertex> &graph, int u, int v) {
    graph[u - 1].adjacent_vertices.push_back(v);
    graph[v - 1].adjacent_vertices.push_back(u);
}

//tries to visit the vertex vert. If vert has'nt been visited yet visit the subtree using depthFirstSearch
//if the vertex vert has been visited there is a loop
void visit(vector<vertex> &graph, vertex &vert, vertex &father) {
    if (error)
        return;
    if (vert.visited == -1) {
        vert.visited = 1;
        if(father.index == vert.index) {
            vert.color = 1;
        } else {
            vert.color = -1*father.color;
        }
        for (auto const &i : vert.adjacent_vertices) {
            if (i != father.index) {
                visit(graph, graph[i - 1], vert);
            }
        }
        vert.visited = 2;
    } else {
        if(father.color == vert.color && father.index != vert.index) {
            error = true;
        }
    }
}

void depthFirstSearch(vector<vertex> &graph) {
    subset_count = 0;
    for (auto &i : graph) {
        if (i.visited == -1) {
            if(error)
                return;
            visit(graph, i, i);
            subset_count++;
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\BUGLIFE\\in.txt");
    int n, m, p;
    cin >> p;
    for (int i = 0; i < p; ++i) {
        cin >> n >> m;
        error = false;
        vector<vertex> graph;
        int u, v;
        for (int k = 0; k < n; ++k) {
            graph.push_back(vertex{k + 1});
        }
        while (m--) {
            cin >> u >> v;
            add_edge(graph, u, v);
        }
        depthFirstSearch(graph);
        if (!error) {
            cout << "Scenario #" << i + 1 << ":\nNo suspicious bugs found!\n";
        } else {
            cout << "Scenario #" << i + 1 << ":\nSuspicious bugs found!\n";
        }
    }
    return 0;
}
