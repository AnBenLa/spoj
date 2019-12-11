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
};

//adds an edge from u to v and an edge from v to u (indices start with 1)
void add_edge(vector<vertex> &graph, us u, us v) {
    graph[u - 1].adjacent_vertices.push_back(v);
    graph[v - 1].adjacent_vertices.push_back(u);
}

//tries to visit the vertex vert. If vert has'nt been visited yet visit the subtree using depthFirstSearch
//if the vertex vert has been visited there is a loop
void visit(vector<vertex>& graph, vertex& vert, vertex& father, vector<vertex>& path){
    if(vert.visited == -1) {
        vert.visited = 1;
        for (auto const &i : vert.adjacent_vertices) {
            if(i != father.index) {
                path.push_back(graph[i-1]);
                visit(graph, graph[i - 1], vert, path);
                path.pop_back();
            }
        }
        vert.visited = 2;
    } else {
        if(path.size() == 2)
            return;
        bool cycle_start = false;
        set<us> cycle;
        for(int i = 0; i < path.size() - 1; ++i){
            if(path[i].index == path[path.size() - 1].index)
                cycle_start = true;
            if(cycle_start)
                cycle.insert(path[i].index);
        }
        if(cycle.size() > 1) {
            bool inserted = false;
            for (auto k : cycle) {
                if(inserted)
                    break;
                for(auto g : cycle) {
                    if(k != g) {
                        for (auto &r : regions) {
                            if (r.find(k) != r.end() && r.find(g) != r.end()) {
                                r.insert(cycle.begin(), cycle.end());
                                inserted = true;
                            }
                        }
                    }
                }
            }
            if(!inserted) {
                regions.push_back(cycle);
            }
        }
    }
}

void depthFirstSearch(vector<vertex> &graph) {
    for (auto &i : graph) {
        if (i.visited == -1) {
            vector<vertex> path;
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
    us t,n,b,u,v,tmp;
    ui e;
    us supply_lookup [260];
    bool city_unused [260];
    vector<vertex> graph;
    vector<us> buzz_energy;
    cin >> t;
    for(us i = 0; i < t; ++i){
        graph.clear();
        regions.clear();
        buzz_energy.clear();
        cin >> n >> e >> b;

        for(us k = 0; k < n; ++k){
            cin >> supply_lookup[k];
            graph.push_back(vertex{k + 1});
            city_unused[k] = true;
        }
        for(us k = 0; k < b; ++k){
            cin >> tmp;
            buzz_energy.push_back(tmp);
        }
        for(ui k = 0; k < e; ++k){
            cin >> u >> v;
            add_edge(graph, u, v);
        }

        //find regions via cycle check
        depthFirstSearch(graph);

        vector<ui> region_energy_supply;

        for(const auto& region : regions){
            ui total_region_energy = 0;
            for(auto city : region){
                city_unused[city - 1] = false;
                total_region_energy += supply_lookup[city - 1];
            }
            region_energy_supply.push_back(total_region_energy);
        }

        for(us k = 0; k < n; ++k){
            if(city_unused[k]){
                region_energy_supply.push_back(supply_lookup[k]);
                city_unused[k] = false;
            }
        }

        cout << "Buzz Mission " << i+1 <<": " << region_energy_supply.size() << " ";
        if(region_energy_supply.size() > b){
            cout << "No\n";
        } else {
            ui max_wastage = 0;
            sort(region_energy_supply.begin(), region_energy_supply.end());
            sort(buzz_energy.begin(), buzz_energy.end());

            //for each region
            vector<ui> min_buzzs;
            for(us k = 0; k < region_energy_supply.size(); ++k){
                //find best buzz
                int min_buzz = -2000;
                short min_ind = -1;
                for(us j = 0; j < buzz_energy.size(); ++j){
                    int current_diff = buzz_energy[j] - region_energy_supply[region_energy_supply.size() - 1 - k];
                    if(current_diff < 0){
                        current_diff = -current_diff;
                    }
                    if(min_ind == -1){
                        min_buzz = current_diff;
                        min_ind = j;
                    } else if (current_diff < min_buzz){
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

        for(us k = 0; k < n; k++){
            supply_lookup[k] = 0;
        }
    }
    return 0;
}
