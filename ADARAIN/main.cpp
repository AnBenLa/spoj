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

lli furrow[1000010]{0};

int main() {
    int n,m,w;
    scanf("%d %d %d", &n, &m, &w);
    while(n--){
        int l,r;
        scanf("%d %d", &l,&r);
        //operation
        furrow[l] += 1;
        furrow[r+1] -= 1;
    }
    for(ui i = 1; i < w; ++i){
        furrow[i] += furrow[i-1];
    }
    while(m--){
        int a;
        scanf("%d", &a);
        printf("%lld\n", furrow[a]);
    }
    return 0;
}
