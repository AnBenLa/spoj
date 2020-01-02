//
// Created by Mortiferum on 28.12.2019.
// https://www.spoj.com/problems/SCITIES/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
typedef unsigned short us;
typedef unsigned int ui;

bool maximizing = true, print_out = false;
us const dim = 101, max_value = 100;
us m, range, t, C1, C2, c1, c2, g, graph[dim][dim], original[dim][dim];
bool    crossed_out[dim][dim],  crossed_out_col[dim],   crossed_out_row[dim],
        assigned[dim][dim],     assigned_col[dim],      assigned_row[dim],
        ocupied_row[dim],       ocupied_col[dim];
ui result;

void print() {
    cout << "\n";
    for (us i = 1; i < range; ++i) {
        for (us j = 1; j < range; ++j) {
            if (!crossed_out_row[i] && !crossed_out_col[j]) {
                cout << graph[i][j] << "\t";
            } else {
                cout << "*\t";
            }
        }
        cout << "\n";
    }
}

void sub_row() {
    for (us i = 1; i < range; ++i) {
        us min = max_value;
        for (us j = 1; j < range; ++j) {
            if (graph[i][j] < min) {
                min = graph[i][j];
            }
        }
        for (us j = 1; j < range; ++j) {
            graph[i][j] -= min;
        }
    }
}

void sub_col() {
    for (us i = 1; i < range; ++i) {
        us min = max_value;
        for (us j = 1; j < range; ++j) {
            if (graph[j][i] < min) {
                min = graph[j][i];
            }
        }
        for (us j = 1; j < range; ++j) {
            graph[j][i] -= min;
        }
    }
}

us find_smallest_entry() {
    us smallest_entry = max_value;
    for (us i = 1; i < range; ++i) {
        for (us j = 1; j < range; ++j) {
            if (!crossed_out_row[i] && !crossed_out_col[j] && graph[i][j] < smallest_entry) {
                smallest_entry = graph[i][j];
            }
        }
    }
    return smallest_entry;
}

us min_lines() {
    us n = 0;
    for (us i = 1; i < range; ++i) {
        crossed_out_col[i] = false;
        crossed_out_row[i] = false;
        assigned_col[i] = false;
        assigned_row[i] = false;
        for(us j = 1; j < range; ++j){
            assigned[i][j] = false;
            crossed_out[i][j] = false;
        }
    }
    for (us i = 1; i < range; ++i) {
        bool zero = false;
        for (us j = 1; j < range; ++j) {
            if (graph[i][j] == 0 && !crossed_out[i][j]) {
                if (!zero) {
                    zero = true;
                    assigned_row[i] = true;
                    assigned[i][j] = true;
                    for (us k = 1; k < range; ++k) {
                        if (graph[k][j] == 0 && k != i) {
                            crossed_out[k][j] = true;
                        }
                    }
                } else {
                    crossed_out[i][j] = true;
                }
            }
        }
    }
    queue<us> new_marked_rows, new_marked_col;
    for (us i = 1; i < range; ++i) {
        if (!assigned_row[i]) {
            crossed_out_row[i] = true;
            new_marked_rows.push(i);
        }
    }
    bool marked = true;
    while (marked) {
        marked = false;
        while (!new_marked_rows.empty()) {
            us row = new_marked_rows.front();
            for (us k = 1; k < range; ++k) {
                if (graph[row][k] == 0 && !crossed_out_col[k]) {
                    crossed_out_col[k] = true;
                    new_marked_col.push(k);
                    marked = true;
                }
            }
            new_marked_rows.pop();
        }
        while (!new_marked_col.empty()) {
            us col = new_marked_col.front();
            for (us i = 1; i < range; ++i) {
                if (assigned[i][col] && !crossed_out_row[i]) {
                    crossed_out_row[i] = true;
                    new_marked_rows.push(i);
                    marked = true;
                }
            }
            new_marked_col.pop();
        }
    }
    for(us i = 1; i < range; ++i){
        crossed_out_row[i] = !crossed_out_row[i];
    }
    for (us i = 1; i < range; ++i) {
        if (crossed_out_row[i])
            n += 1;
        if (crossed_out_col[i])
            n += 1;
    }
    return n;
}

//TODO to slow!!!
void cover_zeros(){
    us covered_zeros = 0;
    us zero_count_row[dim]{0}, zero_count_col[dim]{0};
    for(int i = 1; i < range; ++i){
        for(int j = 1; j < range; ++j){
            if(graph[i][j] == 0) {
                zero_count_col[j] += 1;
                zero_count_row[i] += 1;
            }
        }
    }
    while(covered_zeros != m){
        bool single = false;
        for(int i = 1; i < range; ++i){
            if(zero_count_row[i] == 1){
                for(int j = 1; j < range; ++j){
                    if(graph[i][j] == 0 && zero_count_col[j] == 1){
                        single = true;
                        zero_count_row[i] = 0;
                        zero_count_col[j] = 0;
                        result += original[i][j];
                        covered_zeros += 1;
                        break;
                    }
                }
            }
        }

        if(!single){
            for(int i = 1; i < range; ++i){
                if(zero_count_row[i] == 1){
                    for(int j = 1; j < range; ++j){
                        if(graph[i][j] == 0){
                            single = true;
                            zero_count_row[i] = 0;
                            zero_count_col[j] = 0;
                            result += original[i][j];
                            covered_zeros += 1;
                            break;
                        }
                    }
                }
            }
        }

        if(!single){
            for(int j = 1; j < range; ++j){
                if(zero_count_col[j] == 1){
                    for(int i = 1; i < range; ++i){
                        if(graph[i][j] == 0){
                            single = true;
                            zero_count_row[i] = 0;
                            zero_count_col[j] = 0;
                            result += original[i][j];
                            covered_zeros += 1;
                            break;
                        }
                    }
                }
            }
        }

        if(!single){
            for(int i = 1; i < range; ++i){
                if(zero_count_row[i] != 0){
                    for(int j = 1; j < range; ++j){
                        if(graph[i][j] == 0 && zero_count_col[j] != 0){
                            zero_count_row[i] = 0;
                            zero_count_col[j] = 0;
                            result += original[i][j];
                            covered_zeros += 1;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void hungarian_algorithm() {
    if(print_out)
        print();
    sub_row();
    if(print_out)
        print();
    sub_col();
    if(print_out)
        print();
    us n = min_lines();
    if(print_out)
        print();
    while (n != m) {
        us smallest_entry = find_smallest_entry();
        for(us i = 1; i < range; ++i){
            for(us j = 1; j < range; ++j){
                if(!crossed_out_row[i] && !crossed_out_col[j]){
                    if(graph[i][j] - smallest_entry < 0){
                        graph[i][j] = 0;
                    } else {
                        graph[i][j] -= smallest_entry;
                    }
                }
                if(crossed_out_row[i] && crossed_out_col[j])
                    graph[i][j] += smallest_entry;
            }
        }
        //sub_from_uncrossed_rows(smallest_entry);
        //add_to_crossed_columns(smallest_entry);
        n = min_lines();
        if(print_out)
            print();
    }
    cover_zeros();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\SCITIES\\in.txt");

    cin >> t;

    while (t--) {
        result = 0;
        cin >> C1 >> C2 >> c1 >> c2 >> g;
        m = max(C1, C2);
        range = m + 1;

        for (us i = 1; i < range; ++i) {
            for (us j = 1; j < range; ++j) {
                if(maximizing)
                    graph[i][j] = max_value;
                else
                    graph[i][j] = 0;
                original[i][j] = 0;
            }
            ocupied_row[i] = false;
            ocupied_col[i] = false;
        }

        while (c1+c2+g) {
            if(maximizing){
                graph[c1][c2] = max_value -  g;
            } else {
                graph[c1][c2] = g;
            }
            original[c1][c2] = g;
            cin >> c1 >> c2 >> g;
        }

        hungarian_algorithm();
        cout << result << "\n";
    }

    return 0;
}
