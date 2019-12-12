//
// Created by Mortiferum on 08.12.2019.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>

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


void visit(vector<vertex> &graph, vertex &vert, vertex &father, stack<ui> &traversal_stack) {
    vert.visited = 1;
    traversal_stack.push(vert.index);
    int children = 0;

    for (auto const &i : vert.adjacent_vertices) {
        vertex &child = graph[i - 1];
        if (child.visited == -1 && child.index != father.index) {
            children++;
            child.depth = vert.depth + 1;
            child.low = vert.depth + 1;

            visit(graph, child, vert, traversal_stack);

            vert.low = min(vert.low, child.low);

            if (vert.depth > 0 && child.low >= vert.depth) {
                vert.artic = true;
            }

        } else if (child.index != father.index) {
            vert.low = min(vert.low, child.depth);
        }
    }
    if (vert.depth == 0 && children > 1) {
        vert.artic = true;
    }
    vert.visited = 2;
}


void depthFirstSearch(vector<vertex> &graph, stack<ui> &traversal_stack) {
    for (auto &i : graph) {
        if (i.visited == -1) {
            i.depth = 0;
            i.low = 0;
            visit(graph, i, i, traversal_stack);
        }
    }
}

//adds all reachable nodes in the graph from node with index to vector result
void reachability(vector<vertex> &graph, ui index, vector<ui> &result) {
    for (auto adj_vert : graph[index - 1].adjacent_vertices) {
        vertex &child = graph[adj_vert - 1];
        if (child.visited == -1) {
            child.visited = 1;
            result.push_back(child.index);
            reachability(graph, child.index, result);
        }
    }
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\CAPCITY\\in.txt");

    ui n, m, u, v;
    cin >> n >> m;
    vector<vertex> graph;
    vector<vertex> compl_graph;
    for (int i = 0; i < n; ++i) {
        graph.push_back({i + 1});
        compl_graph.push_back({i + 1});
    }

    while (m--) {
        cin >> u >> v;
        graph[u - 1].adjacent_vertices.push_back(v);
        compl_graph[v - 1].adjacent_vertices.push_back(u);
    }

    stack<ui> traversal_stack;
    depthFirstSearch(graph, traversal_stack);

    vector<vector<ui>> sccs;
    while (!traversal_stack.empty()) {
        ui current = traversal_stack.top();
        traversal_stack.pop();
        vector<ui> scc;
        reachability(compl_graph, current, scc);
        sccs.push_back(scc);
    }


    int result = 0;
    for (auto const &vert : graph) {
        if (vert.artic)
            result++;
    }
    cout << result << "\n";

    return 0;
}
