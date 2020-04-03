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

int main() {
    ui t,n,s,e;
    scanf("%d", &t);
    while(t--){
        vector<pair<int,int>> ac, sol;
        scanf("%d", &n);
        for(ui i = 0; i < n; ++i){
            scanf("%d %d",&s,&e);
            ac.push_back({s,e});
        }
        sort(begin(ac), end(ac), [](pair<int,int> a, pair<int,int> b) {return a.second < b.second; });
        for(ui i = 0; i < n; ++i){
            if(sol.size() == 0 || ac[i].first >= sol.rbegin()->second)
                sol.push_back(ac[i]);
        }
        printf("%d\n", sol.size());
    }
    return 0;
}
