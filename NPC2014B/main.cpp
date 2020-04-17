#include<bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>

using namespace std;
typedef unsigned short us;
typedef unsigned long long int ulli;
typedef unsigned long long ull;
typedef long long int lli;
typedef unsigned int ui;

ui n, tmp, arr[5010], min = 0, tot = 0;

lli decide(ui from, ui to, lli cost_so_far) {
    if (from > to || from == to) {
        return 0;
    } else if (from + 1 == to) {
        // can always be painted in one stroke vertically
        return 1;
    }

    lli all_vert_cost = to - from;

    //find minimum in between borders
    lli new_hor_cost = 0;
    for (ui i = from; i < to; ++i) {
        if (new_hor_cost == 0 || arr[i] < new_hor_cost)
            new_hor_cost = arr[i];
    }

    //check what the cost would be if we paint horizontally as high as we can
    lli hor_cost = new_hor_cost - cost_so_far;
    for (int i = from; i < to; ++i) {
        if (arr[i] != new_hor_cost) {
            //find next segment after the subtraction of m
            int j = i + 1;
            while (j < to && arr[j] != new_hor_cost)
                j++;
            hor_cost += decide(i, j, new_hor_cost);
            i = j;
        }
    }
    lli result = std::min(all_vert_cost, hor_cost);
    return result;
}

int main() {
    scanf("%u", &n);

    for (ui i = 0; i < n; ++i) {
        scanf("%u", &tmp);
        arr[i] = tmp;
    }

    printf("%lld\n", decide(0, n, 0));

    return 0;
}
