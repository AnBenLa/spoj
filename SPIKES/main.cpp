//https://www.spoj.com/problems/SPIKES/
#include <iostream>
#include <vector>
#include <fstream>
using  namespace std;

bool possible = false;
int tot = 0;

void find_treasure(vector<vector<int>>& maze, pair<int,int> pos, int j){
    if(j < (tot+1)/2)
        return;

    if(maze.at(pos.first).at(pos.second) == 100){
        possible = true;
        return;
    }

    vector<pair<int,int>> options;

    if(pos.second < maze.at(pos.first).size() - 1){
        if(maze.at(pos.first).at(pos.second + 1) != 1){
            options.push_back(pair<int,int>(pos.first, pos.second + 1));
        }
    }

    if(pos.second > 0){
        if(maze.at(pos.first).at(pos.second - 1) != 1){
            options.push_back(pair<int,int>(pos.first, pos.second - 1));
        }
    }

    if(pos.first > 0){
        if(maze.at(pos.first - 1).at(pos.second) != 1){
            options.push_back(pair<int,int>(pos.first - 1, pos.second));
        }
    }

    if(pos.first < maze.size() - 1){
        if(maze.at(pos.first + 1).at(pos.second) != 1){
            options.push_back(pair<int,int>(pos.first + 1, pos.second));
        }
    }

    for(auto option : options){
        int tmp = maze.at(pos.first).at(pos.second);
        maze.at(pos.first).at(pos.second) = 1;
        if(maze.at(option.first).at(option.second) == -1) {
            find_treasure(maze, option, j - 1);
        } else {
            find_treasure(maze, option, j);
        }
        maze.at(pos.first).at(pos.second) = tmp;
    }
}

int main() {
    int n, m, j;
    char tmp;
    vector<vector<int>> maze;
    vector<pair<int,int>> starting_points;

    ifstream inFile ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\15609\\in.txt");

    inFile >> n >> m >> j;
    tot = j;

    for (int i = 0; i < n; ++i) {
        vector<int> row;
        for(int j = 0; j < m; ++j){
            inFile >> tmp;
            if(tmp == '@'){
                row.push_back(9);
                starting_points.push_back(pair<int,int>(i,j));
            } else if(tmp == '.'){
                row.push_back(0);
            } else if(tmp == '#'){
                row.push_back(1);
            } else if(tmp == 's'){
                row.push_back(-1);
            } else if(tmp == 'x'){
                row.push_back(100);
            }
        }
        maze.push_back(row);
    }

    for(auto p : starting_points){
        maze.at(p.first).at(p.second) = 1;
         find_treasure(maze, p , j);
        maze.at(p.first).at(p.second) = 9;
    }
    if(possible){
        cout << "SUCCESS";
    } else {
        cout << "IMPOSSIBLE";
    }
    return 0;
}