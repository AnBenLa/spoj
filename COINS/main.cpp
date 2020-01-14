//
// Created by Mortiferum on 12.01.2020.
// https://www.spoj.com/problems/COINS/

#include <iostream>
#include <fstream>

using namespace std;
typedef unsigned int ui;
typedef unsigned long long int ulli;

ulli memory[1000000]{0};

ulli compute_profit(ulli n) {
    if (n > 1000000 || (memory[n] == 0 && n > 0)) {
        ui l = n / 2, m = n / 3, o = n / 4;
        ulli split = compute_profit(l) + compute_profit(m) + compute_profit(o);
        if (n < 1000000) {
            if (split > n)
                memory[n] = split;
            else
                memory[n] = n;
        } else {
            if (split > n)
                return split;
            else
                return n;
        }
    }

    return memory[n];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\COINS\\in.txt");
    ulli n, profit;
    memory[1] = 1;
    while (cin >> n) {
        profit = compute_profit(n);
        cout << profit << "\n";
    }
    return 0;
}