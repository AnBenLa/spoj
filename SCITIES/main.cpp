//
// Created by Mortiferum on 28.12.2019.
// https://www.spoj.com/problems/SCITIES/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned short us;
typedef unsigned int ui;

bool maximizing = true, print_out = false;
us const dim = 101, max_value = 100;
us path[dim][2]{0};
us m, range, t, C1, C2, c1, c2, g, graph[dim][dim], original[dim][dim], assignment [dim][dim]{0};
bool    crossed_out_col[dim], crossed_out_row[dim],
        covered_row[dim]{false}, covered_col[dim]{false};
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
        cout << "\t\t";
        for (us j = 1; j < range; ++j) {
            if (!covered_row[i] && !covered_col[j]) {
                cout << graph[i][j] << "\t";
            } else {
                cout << "*\t";
            }
        }
        cout << "\t\t";
        for (us j = 1; j < range; ++j) {
            if (assignment[i][j] == 1) {
                cout <<"*\t";
            } else if(assignment[i][j] == 2) {
                cout << "'\t";
            } else {
                cout << "0\t";
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
            if (!covered_row[i] && !covered_col[j] && graph[i][j] < smallest_entry) {
                smallest_entry = graph[i][j];
            }
        }
    }
    return smallest_entry;
}

bool check_matching(){
    bool matching = true;
    for(int i = 1; i < range; ++i){
        for(int j = 1; j < range; ++j){
            if(assignment[i][j] == 1)
                covered_col[j] = true;
        }
    }
    for(int i = 1; i < range; ++i){
        if(!covered_col[i])
            matching = false;
    }
    return matching;
}

int find_path(us i, us j){
    ui position = 0;
    path[position][0] = i;
    path[position][1] = j;
    bool done = false;
    while(!done){
        bool star_in_col = false, prime_in_row = false;
        for(us i = 1; i < range; ++i){
            if(assignment[i][path[position][1]] == 1){
                position += 1;
                path[position][0] = i;
                path[position][1] = path[position - 1][1];
                star_in_col = true;
                break;
            }
        }
        if(!star_in_col){
            done = true;
        }
        if(!done){
            for(us k = 1; k < range; ++k){
                if(assignment[path[position][0]][k] == 2){
                    position += 1;
                    path[position][0] = path[position - 1][0];
                    path[position][1] = k;
                    prime_in_row = true;
                    break;
                }
            }
        }
    }
    return position;
}

void augment_path(ui path_steps){
    for(ui i = 0; i <= path_steps; ++i){
        if(assignment[path[i][0]][path[i][1]] == 1)
            assignment[path[i][0]][path[i][1]] = 0;
        else
            assignment[path[i][0]][path[i][1]] = 1;
    }
}

void reset_cover(){
    for(int i = 1; i < range; ++i){
        covered_col[i] = false;
        covered_row[i] = false;
    }
}

void initial_assignment(){
    for(us i = 1; i < range; ++i){
        for(us j = 1; j < range; ++j){
            if(graph[i][j] == 0 && !covered_row[i] && !covered_col[j]){
                assignment[i][j] = 1;
                covered_row[i] = true;
                covered_col[j] = true;
            }
        }
    }
    reset_cover();
}

void min_add_sub(){
    us smallest_entry = find_smallest_entry();
    for (us i = 1; i < range; ++i) {
        for (us j = 1; j < range; ++j) {
            if (!covered_row[i] && !covered_col[j]) {
                if (graph[i][j] - smallest_entry < 0) {
                    graph[i][j] = 0;
                } else {
                    graph[i][j] -= smallest_entry;
                }
            }
            if (covered_row[i] && covered_col[j])
                graph[i][j] += smallest_entry;
        }
    }
}

pair<us,us> process_uncovered_zeros(){
   for(int i = 1; i < range; ++i){
       for(int j = 1; j < range; ++j){
          if(graph[i][j] == 0 && !covered_row[i] && !covered_col[j]){
              //prime the uncovered zero
              assignment[i][j] = 2;
              bool starred_zero_found = false;
              //check if row contains starred zero
              for(int k = 1; k < range; ++k){
                  if(assignment[i][k] == 1){
                      covered_row[i] = true;
                      covered_col[k] = false;
                      starred_zero_found = true;
                      break;
                  }
              }
              if(!starred_zero_found){
                  return {i,j};
              }
          }
       }
   }
    return {0,0};
}

void compute_result(){
    for(int i = 1; i < range; ++i){
        for(int j = 1; j < range; ++j){
            if(assignment[i][j] == 1)
                result += original[i][j];
        }
    }
}

void erase_primes(){
    for(int i = 1; i < range; ++i){
        for(int j = 1; j < range; ++j){
            if(assignment[i][j] == 2)
                assignment[i][j] = 0;
        }
    }
}

void hungarian_algorithm() {
    //https://www2.cs.fau.de/teaching/SS2015/HalloWelt/FSB2_2015.pdf
    //http://csclab.murraystate.edu/~bob.pilgrim/445/munkres.html
    //star == 1, strich == 2

    if (print_out)
        print();

    sub_row();

    if (print_out)
        print();

    sub_col();

    if (print_out)
        print();

    initial_assignment();

    bool finished = false;
    while(!finished){
        if(print_out)
            print();
        pair<us,us> unprocessed_zero = process_uncovered_zeros();

        if(print_out)
            print();

        if(unprocessed_zero.first != 0) {
            ui steps = find_path(unprocessed_zero.first,unprocessed_zero.second);
            augment_path(steps);
            reset_cover();
            erase_primes();

            if(print_out)
                print();

            finished = check_matching();
            continue;
        }

        min_add_sub();

    }
    compute_result();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\SCITIES\\in-2.txt");

    cin >> t;

    while (t--) {
        result = 0;
        cin >> C1 >> C2 >> c1 >> c2 >> g;
        m = max(C1, C2);
        range = m + 1;

        for (us i = 1; i < range; ++i) {
            for (us j = 1; j < range; ++j) {
                if (maximizing)
                    graph[i][j] = max_value;
                else
                    graph[i][j] = 0;
                original[i][j] = 0;
                assignment[i][j] = 0;
            }
            covered_col[i] = false;
            covered_row[i] = false;
        }

        while (c1 + c2 + g) {
            if (maximizing) {
                graph[c1][c2] = max_value - g;
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
