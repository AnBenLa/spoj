//
// Created by Mortiferum on 28.12.2019.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
typedef unsigned short us;
typedef unsigned int ui;


bool maximizing = true;
us const dim = 101, max_value = 300;
us m, range;
us graph[dim][dim], original[dim][dim];
bool crossed_out_col[dim], crossed_out_row[dim],assigned[dim][dim],
        assigned_col[dim], assigned_row[dim], active[dim][dim],
        ocupied_row[dim], ocupied_col[dim];
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
            if (graph[i][j] < min && active[i][j]) {
                min = graph[i][j];
            }
        }
        for (us j = 1; j < range; ++j) {
            if (active[i][j]) {
                graph[i][j] -= min;
            }
        }
    }
}

void sub_col() {
    for (us i = 1; i < range; ++i) {
        us min = max_value;
        for (us j = 1; j < range; ++j) {
            if (graph[j][i] < min && active[j][i]) {
                min = graph[j][i];
            }
        }
        for (us j = 1; j < range; ++j) {
            if (active[j][i]) {
                graph[j][i] -= min;
            }
        }
    }
}

us find_smallest_entry() {
    us smallest_entry = max_value;
    for (us i = 1; i < range; ++i) {
        for (us j = 1; j < range; ++j) {
            if (!crossed_out_row[i] && !crossed_out_col[j] && active[i][j] && graph[i][j] < smallest_entry) {
                smallest_entry = graph[i][j];
            }
        }
    }
    return smallest_entry;
}

void sub_from_uncrossed_rows(us smallest_entry) {
    for (us i = 1; i < range; ++i) {
        for (us j = 1; j < range; ++j) {
            if (active[i][j] && !crossed_out_row[i]) {
                if(graph[i][j] - smallest_entry < 0){
                    graph[i][j] = 0;
                } else {
                    graph[i][j] -= smallest_entry;
                }
            }
        }
    }
}

void add_to_crossed_columns(us smallest_entry) {
    for (us i = 1; i < range; ++i) {
        for (us j = 1; j < range; ++j) {
            if (active[i][j] && crossed_out_col[j]) {
                graph[i][j] += smallest_entry;
            }
        }
    }
}

us min_lines() {
    us n = 0;
    bool crossed_out[dim][dim];
    for (us i = 1; i < range; ++i) {
        crossed_out_col[i] = false;
        crossed_out_row[i] = false;
        assigned_col[i] = false;
        assigned_row[i] = false;
        for(us j = 1; j < range; ++j){
            assigned[i][j] = false;
        }
    }
    for (us i = 1; i < range; ++i) {
        bool zero = false;
        for (us j = 1; j < range; ++j) {
            if (graph[i][j] == 0 && active[i][j] && !crossed_out[i][j]) {
                if (!zero) {
                    zero = true;
                    assigned_row[i] = true;
                    assigned[i][j] = true;
                    for (us k = 1; k < range; ++k) {
                        if (graph[k][j] == 0 && active[i][j] && k != i) {
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
                if (graph[row][k] == 0 && active[row][k] && !crossed_out_col[k]) {
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
                if (active[i][col] && assigned[i][col] && !crossed_out_row[i]) {
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

bool cover_zeros(us open){
    if(open == 0)
        return true;
    else{
        for(us i = 1; i < range; ++i){
            for(us j = 1; j < range; ++j){
                if(graph[i][j] == 0 && !ocupied_row[i] && !ocupied_col[j]){
                    ocupied_row[i] = true;
                    ocupied_col[j] = true;
                    result += original[i][j];
                    if(cover_zeros(open - 1)){
                        return true;
                    }
                    result -= original[i][j];
                    ocupied_row[i] = false;
                    ocupied_col[j] = false;
                }
            }
        }
        return false;
    }
}

void compute_result() {
    bool test = cover_zeros(m);
}

void hungarian_algorithm() {
    print();
    sub_row();
    print();
    sub_col();
    print();
    us n = min_lines();
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
        print();
    }
    compute_result();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Elke\\Desktop\\Anton\\Competetive-Programming\\spoj\\SCITIES\\in.txt");

    us t, C1, C2, c1, c2, g;

    cin >> t;

    while (t--) {
        result = 0;
        for (us i = 0; i <= dim; ++i) {
            for (us j = 0; j <= dim; ++j) {
                graph[i][j] = 0;
                original[i][j] = 0;
                active[i][j] = false;
            }
            ocupied_row[i] = false;
            ocupied_col[i] = false;
        }
        cin >> C1 >> C2 >> c1 >> c2 >> g;
        m = max(C1, C2);
        range = m + 1;
        while (!(c1 == 0 && c2 == 0 && g == 0)) {
            if(maximizing){
                graph[c1][c2] = max_value -  g;
            } else {
                graph[c1][c2] = g;
            }
            original[c1][c2] = g;
            active[c1][c2] = true;
            cin >> c1 >> c2 >> g;
        }

        for(us i = 1; i < range; ++i){
            for(us j = 1; j < range; ++j){
                if(!active[i][j]){
                    graph[i][j] = max_value;
                    active[i][j] = true;
                }
            }
        }

        hungarian_algorithm();
        cout << "\nresult: " << result << "\n";
    }

    return 0;
}
