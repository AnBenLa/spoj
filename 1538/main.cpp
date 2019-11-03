//https://www.spoj.com/problems/MKJUMPS/
#include <iostream>
#include <vector>
#include <fstream>

using  namespace std;

int max_visited = -1;

void find_unreach_fields(vector<vector<bool>>& field, pair<int,int> const& p, int visited){
    if(visited > max_visited)
        max_visited = visited;
    field.at(p.second).at(p.first) = false;

    pair<int,int> p1, p2, p3, p4, p5, p6, p7, p8;

    p1.first = p.first - 2;
    p1.second = p.second - 1;
    p2.first = p.first - 2;
    p2.second = p.second + 1;
    p3.first = p.first - 1;
    p3.second = p.second - 2;
    p4.first = p.first - 1;
    p4.second = p.second + 2;
    p5.first = p.first + 1;
    p5.second = p.second - 2;
    p6.first = p.first + 1;
    p6.second = p.second + 2;
    p7.first = p.first + 2;
    p7.second = p.second - 1;
    p8.first = p.first + 2;
    p8.second = p.second + 1;

    vector<pair<int,int>> options {p1, p2, p3, p4, p5, p6, p7, p8};

    for(pair<int,int> op : options){
        //check if option is valid
        if(field.size() - 1 >= op.second){
            if(field.at(op.second).size() - 1 >= op.first){
                if(field.at(op.second).at(op.first)){
                    find_unreach_fields(field, op, visited + 1);
                    field.at(op.second).at(op.first) = true;
                }
            }
        }
    }
}

int main() {
    int rows, itt = 1;

    ifstream inFile ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\1538\\in.txt");

    while(true){
        max_visited = -1;
        int total_fields = 0;
        inFile >> rows;
        if(rows == 0)
            break;
        vector<vector<bool>> field;
        while(inFile.peek() != '\n' && inFile.peek() != '\r'){
            int elements, offset;
            vector<bool> row;
            inFile >> offset >> elements;
            for(int i = 0; i < offset; ++i) {
                row.push_back(false);
            }
            for(int i = 0; i < elements; ++i) {
                row.push_back(true);
                total_fields += 1;
            }
            field.push_back(row);
        }
        pair<int,int> position (0,0);
        find_unreach_fields(field, position,1);
        int f = total_fields - max_visited;
        if(f == 1)
            cout << "Case " << itt << ", " << f << " square can not be reached." << endl;
        else
            cout << "Case " << itt << ", " << f << " squares can not be reached." << endl;
        itt += 1;
    }
    return 0;
}