//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/DCEPC501/

#include <iostream>
#include <vector>
#include <fstream>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

lli t, n, toys[100030]{0}, memory[100030]{0};

lli find_max() {
    lli m = 0;
    for (lli i = 0; i < n; i += 2) {
        // from the current maximum for the selected position
        lli cur = 0;
        if (i > 1)
            cur = memory[i - 1];

        // check select one
        lli value = toys[i] + cur;
        if (value > memory[i + 1])
            memory[i + 1] = value;
        // check select two
        value += toys[i + 1];
        if (value > memory[i + 3])
            memory[i + 3] = value;
        // check select three
        value += toys[i + 2];
        if (value > memory[i + 5])
            memory[i + 5] = value;

        // select maximum value
        m = max(memory[i + 1], max(memory[i + 3], memory[i + 5]));
    }
    return m;
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &n);
        for (lli i = 0; i < n; ++i)
            cin >> toys[i];
        printf("%lld\n", find_max());
        for (lli i = 0; i < n + 6; ++i)
            toys[i] = memory[i] = 0;
    }
    return 0;
}