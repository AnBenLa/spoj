//
// Created by Mortiferum on 08.12.2019.
//
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

lli furrow[10010]{0};

int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        int n, u;
        scanf("%d %d", &n, &u);
        while (u--) {
            int l, r, val;
            scanf("%d %d %d", &l, &r, &val);
            //operation
            furrow[l] += val;
            furrow[r + 1] -= val;
        }
        for (ui i = 1; i < n; ++i) {
            furrow[i] += furrow[i - 1];
        }
        int q;
        scanf("%d",&q);
        while (q--) {
            int a;
            scanf("%d", &a);
            printf("%lld\n", furrow[a]);
        }
        for (ui i = 0; i < n; ++i) {
            furrow[i] = 0;
        }
    }
    return 0;
}
