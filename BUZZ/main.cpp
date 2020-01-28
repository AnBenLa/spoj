//
// Created by Mortiferum on 08.12.2019.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;
typedef unsigned short us;
typedef unsigned int ui;

vector<set<us>> regions;

struct edge{
    int a,b;
};

struct vertex {
    int index;
    vector<us> adjacent_vertices;
    int visited = -1;
    ui low;
    ui depth;
    bool artic = false;
};

//adds an edge from u to v and an edge from v to u (indices start with TEST)
void add_edge(vector<vertex> &graph, us u, us v) {
    graph[u - 1].adjacent_vertices.push_back(v);
    graph[v - 1].adjacent_vertices.push_back(u);
}

//tries to visit the vertex vert. If vert has'nt been visited yet visit the subtree using depthFirstSearch
//if the vertex vert has been visited there is a loop
void visit(vector<vertex> &graph, vertex &vert, vertex &father, vector<edge> &path) {
    vert.visited = 1;
    for (auto const &i : vert.adjacent_vertices) {
        vertex& child = graph[i - 1];
        if (child.visited == -1) {
            child.depth = vert.depth + 1;
            child.low = vert.depth + 1;
            path.push_back({vert.index,child.index});
            visit(graph, child, vert, path);
            vert.low = min(vert.low, child.low);
            if((vert.depth == 0 && vert.adjacent_vertices.size() > 1) ||
                    (vert.depth > 0 && child.low >= vert.depth)){
                set<us> region;
                vert.artic = true;
                //TODO fix problem here
                while(path.back().a != vert.index || path.back().b != child.index){
                    //cout << path.back().a << " -- " << path.back().b << " ";
                    region.insert(path.back().a);
                    region.insert(path.back().b);
                    path.pop_back();
                }
                //cout << path.back().a << " -- " << path.back().b << "\n";
                region.insert(path.back().a);
                region.insert(path.back().b);
                if(region.size() > 2) {
                    regions.push_back(region);
                }
                path.pop_back();

            }
        } else if(child.index != father.index){
            vert.low = min(vert.low, child.depth);
            if(child.depth < vert.depth){
                path.push_back({vert.index, child.index});
            }
        }
    }
    vert.visited = 2;
}


void depthFirstSearch(vector<vertex> &graph) {
    for (auto &i : graph) {
        if (i.visited == -1) {
            vector<edge> path;
            i.depth = 0;
            i.low = 0;
            visit(graph, i, i, path);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\BUZZ\\in.txt");

    ui e, t, n, b, u, v, tmp;
    us supply_lookup[300];
    bool city_unused[300];
    vector<vertex> graph;
    vector<us> buzz_energy;

    cin >> t;
    for (us i = 0; i < t; ++i) {
        //clear data
        graph.clear();
        regions.clear();
        buzz_energy.clear();

        cin >> n >> e >> b;

        //read in city supply values and store them
        for (us k = 0; k < n; ++k) {
            cin >> supply_lookup[k];
            graph.push_back(vertex{k + 1});
            city_unused[k] = true;
        }
        //read in the energies required by the buzz figures
        for (us k = 0; k < b; ++k) {
            cin >> tmp;
            buzz_energy.push_back(tmp);
        }
        //read in all the edges and construct the graph
        for (ui k = 0; k < e; ++k) {
            cin >> u >> v;
            add_edge(graph, u, v);
        }

        //find regions via dfs hopcroft and tarjan algorithm
        depthFirstSearch(graph);

        //compute energy supply per region
        vector<ui> region_energy_supply;

        for (const auto &region : regions) {
            ui total_region_energy = 0;
            for (auto city : region) {
                city_unused[city - 1] = false;
                total_region_energy += supply_lookup[city - 1];
            }
            region_energy_supply.push_back(total_region_energy);
        }

        for (us k = 0; k < n; ++k) {
            if (city_unused[k]) {
                region_energy_supply.push_back(supply_lookup[k]);
                city_unused[k] = false;
            }
        }

        cout << "Buzz Mission " << i + 1 << ": " << region_energy_supply.size() << " ";
        if (region_energy_supply.size() > b) {
            cout << "No\n";
        } else {
            //compute the minimal wastage of energy
            ui max_wastage = 0;
            sort(region_energy_supply.begin(), region_energy_supply.end());
            sort(buzz_energy.begin(), buzz_energy.end());

            //for each region
            vector<ui> min_buzzs;
            for (us k = 0; k < region_energy_supply.size(); ++k) {
                //find best buzz
                int min_buzz = -2000;
                short min_ind = -1;
                for (us j = 0; j < buzz_energy.size(); ++j) {
                    int current_diff = buzz_energy[j] - region_energy_supply[region_energy_supply.size() - 1 - k];
                    if (current_diff < 0) {
                        current_diff = -current_diff;
                    }
                    if (min_ind == -1) {
                        min_buzz = current_diff;
                        min_ind = j;
                    } else if (current_diff < min_buzz) {
                        min_buzz = current_diff;
                        min_ind = j;
                    }
                }
                min_buzzs.push_back(min_buzz);
                buzz_energy[min_ind] = 50000;
            }
            sort(min_buzzs.begin(), min_buzzs.end());
            max_wastage = min_buzzs[min_buzzs.size() - 1];
            cout << max_wastage << "\n";
        }

        for (us k = 0; k < n; k++) {
            supply_lookup[k] = 0;
        }
    }
    return 0;
}
