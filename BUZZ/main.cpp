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
void visit(vector<vertex> &graph, vertex &vert, vertex &father, vector<vertex> &path) {
    vert.visited = 1;
    bool artic = false;
    for (auto const &i : vert.adjacent_vertices) {
        vertex& child = graph[i - 1];
        if (child.index != father.index && child.visited == -1) {
            child.depth = vert.depth + 1;
            child.low = vert.depth + 1;
            path.push_back(child);
            visit(graph, child, vert, path);
            vert.low = min(vert.low, child.low);
            if((vert.depth == 0 && vert.adjacent_vertices.size() > 1) ||
                    (vert.depth > 0 && child.low >= vert.depth)){
                set<us> region;
                vert.artic = true;
                cout << "Region: ";
                while(path[path.size() - 1].index != child.index ||path[path.size() - 2].index != vert.index){
                    cout << path.back().index << " -- ";
                    region.insert(path.back().index);
                    path.pop_back();
                }
                cout << path[path.size() - 1].index << " -- " << path[path.size() - 2].index << "\n";
                region.insert(path[path.size() - 1].index);
                region.insert(path[path.size() - 2].index);
                path.pop_back();
                regions.push_back(region);
            }
        } else if(child.index != father.index){
            vert.low = min(vert.low, child.depth);
            if(child.depth < vert.depth){
                //path.push_back(child);
            }
        }
    }
    vert.visited = 2;
}


void depthFirstSearch(vector<vertex> &graph) {
    for (auto &i : graph) {
        if (i.visited == -1) {
            vector<vertex> path;
            i.depth = 0;
            i.low = 0;
            path.push_back(i);
            visit(graph, i, i, path);
            path.pop_back();
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\BUZZ\\in.txt");
    us t, n, b, u, v, tmp;
    ui e;
    us supply_lookup[260];
    bool city_unused[260];
    vector<vertex> graph;
    vector<us> buzz_energy;
    cin >> t;
    for (us i = 0; i < t; ++i) {
        graph.clear();
        regions.clear();
        buzz_energy.clear();
        cin >> n >> e >> b;

        for (us k = 0; k < n; ++k) {
            cin >> supply_lookup[k];
            graph.push_back(vertex{k + 1});
            city_unused[k] = true;
        }
        for (us k = 0; k < b; ++k) {
            cin >> tmp;
            buzz_energy.push_back(tmp);
        }
        for (ui k = 0; k < e; ++k) {
            cin >> u >> v;
            add_edge(graph, u, v);
        }

        //find regions via cycle check
        depthFirstSearch(graph);

        //clean regions
        for(int k = 0; k < regions.size(); ++k){
            set<us>& region = regions[k];
            if(region.size() == 2){
                auto it = region.begin();
                us first = *it;
                it++;
                us second = *it;
                if(graph[first - 1].artic && !graph[second - 1].artic){
                    region.erase(first);
                } else if (!graph[first - 1].artic && graph[second - 1].artic){
                    region.erase(second);
                } else {
                    region.clear();
                    regions.push_back(set<us>{first});
                    regions.push_back(set<us>{second});
                }
            }
        }
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
                buzz_energy[min_ind] = 10000;
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
