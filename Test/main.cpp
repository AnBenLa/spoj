//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/TULIPNUM/

#include <iostream>
#include <vector>
#include <fstream>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ui t, n;
ulli max_v;
ui toys[100010];
ulli max_at_i[100010];

void choose(ulli value, ui index) {
    if (max_at_i[index] >= value && value > 0)
        return;
    else
        max_at_i[index] = value;

    if (index >= n) {
        if (max_v < value)
            max_v = value;
        return;
    }
    for (ui i = 1; i <= 3; ++i) {
        value += toys[index + i - 1];
        choose(value, index + 2 * i);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\Test\\in.txt");

    cin >> t;
    while (t--) {
        max_v = 0;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> toys[i];
            max_at_i[i] = 0;
        }
        choose(0, 0);
        cout << max_v << "\n";
    }
    return 0;
}