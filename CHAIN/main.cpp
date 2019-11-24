//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/CHAIN/

#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_set>
#include <chrono>

#define ui unsigned int

using namespace std;

enum type {
    A, B, C, U
};

ui t, n, k, a, x, y, err;
unordered_set<ui> A_S, B_S, C_S;
vector<pair<ui, ui>> unknown_g;
vector<pair<ui, ui>> unknown_e;
type x_t, y_t;

void find_type_x_y() {
    x_t = U;
    y_t = U;
    if (A_S.find(x) != A_S.end())
        x_t = A;
    else if (B_S.find(x) != B_S.end())
        x_t = B;
    else if (C_S.find(x) != C_S.end())
        x_t = C;
    if (A_S.find(y) != A_S.end())
        y_t = A;
    else if (B_S.find(y) != B_S.end())
        y_t = B;
    else if (C_S.find(y) != C_S.end())
        y_t = C;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\CHAIN\\in.txt");

    cin >> t;

    while (t--) {
        A_S.clear();
        B_S.clear();
        C_S.clear();
        unknown_e.clear();
        unknown_g.clear();
        err = 0;
        cin >> n >> k;
        while (k--) {
            cin >> a >> x >> y;
            if (x > n || y > n) {
                err += 1;
                continue;
            }
            find_type_x_y();
            if (a == 1) {
                if (x_t != U && y_t == U) {
                    if (x_t == A)
                        A_S.insert(y);
                    else if (x_t == B)
                        B_S.insert(y);
                    else if (x_t == C)
                        C_S.insert(y);
                } else if (x_t == U && y_t != U) {
                    if (y_t == A)
                        A_S.insert(x);
                    else if (y_t == B)
                        B_S.insert(x);
                    else if (y_t == C)
                        C_S.insert(x);
                } else if (x_t == U && y_t == U) {
                    if (A_S.empty()) {
                        A_S.insert(x);
                        A_S.insert(y);
                    } else {
                        unknown_g.emplace_back(x, y);
                    }
                } else {
                    if (x != y) {
                        err += 1;
                    }
                }
            } else {
                if (x_t == U && y_t == U) {
                    if (A_S.empty()) {
                        A_S.insert(x);
                        B_S.insert(y);
                    } else {
                        unknown_e.emplace_back(x, y);
                    }
                } else if (x_t == U && y_t != U) {
                    if (y_t == A)
                        C_S.insert(x);
                    else if (y_t == B)
                        A_S.insert(x);
                    else if (y_t == C)
                        B_S.insert(x);
                } else if (x_t != U && y_t == U) {
                    if (x_t == A)
                        B_S.insert(y);
                    else if (x_t == B)
                        C_S.insert(y);
                    else if (x_t == C)
                        A_S.insert(y);
                } else {
                    if (x_t == A && y_t != B)
                        err += 1;
                    if (x_t == B && y_t != C)
                        err += 1;
                    if (x_t == C && y_t != A)
                        err += 1;
                }
            }
            //check if unknown elements can be processed
            for (int i = 0; i < unknown_e.size(); ++i) {
                x = unknown_e[i].first;
                y = unknown_e[i].second;
                find_type_x_y();
                if (x_t == A)
                    B_S.insert(y);
                else if (x_t == B)
                    C_S.insert(y);
                else if (x_t == C)
                    A_S.insert(y);
                if (y_t == A)
                    C_S.insert(x);
                else if (y_t == B)
                    A_S.insert(x);
                else if (y_t == C)
                    B_S.insert(x);
                if (y_t != U || x_t != U) {
                    unknown_e.erase(unknown_e.begin() + i);
                    i -= 1;
                }
            }

            for (int i = 0; i < unknown_g.size(); ++i) {
                x = unknown_g[i].first;
                y = unknown_g[i].second;
                find_type_x_y();
                if (x_t == A)
                    A_S.insert(y);
                else if (x_t == B)
                    B_S.insert(y);
                else if (x_t == C)
                    C_S.insert(y);
                if (y_t == A)
                    A_S.insert(x);
                else if (y_t == B)
                    B_S.insert(x);
                else if (y_t == C)
                    C_S.insert(x);
                if (y_t != U || x_t != U) {
                    unknown_g.erase(unknown_g.begin() + i);
                    i -= 1;
                }
            }
        }
        cout << err << "\n";
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}