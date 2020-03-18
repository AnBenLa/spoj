//
// Created by Mortiferum on 08.12.2019.
// Construction of suffix array used from: https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
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

const ulli max_dim = 100010;
char word[max_dim]{'\n'};
ulli suff_ind[max_dim], ord[max_dim], lcp[max_dim], rankt[max_dim], size;

struct suffix{
    int index; // To store original index
    int rank[2]; // To store ranks and next rank pair
};

int cmp(struct suffix a, struct suffix b){
    return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):
           (a.rank[0] < b.rank[0] ?1: 0);
}

void buildSuffixArray(char *txt, int n){
    struct suffix suffixes[n];
    for (int i = 0; i < n; i++){
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
    }

    sort(suffixes, suffixes+n, cmp);
    int ind[n];
    for (int k = 4; k < 2*n; k = k*2){
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;
        for (int i = 1; i < n; i++){
            if (suffixes[i].rank[0] == prev_rank &&
                suffixes[i].rank[1] == suffixes[i-1].rank[1]){
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            } else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }
        for (int i = 0; i < n; i++){
            int nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (nextindex < n)?suffixes[ind[nextindex]].rank[0]: -1;
        }
        sort(suffixes, suffixes+n, cmp);
    }
    for (int i = 0; i < n; i++)
        suff_ind[i] = suffixes[i].index;

}

int main() {

    scanf("%s", word);
    size = strlen(word);
    buildSuffixArray(word,size);
    int k = 0;

    for (int i = 0; i < size; i++) rankt[suff_ind[i]] = i;
    for (int i = 0; i < size; i++, k ? k-- : 0) {
        if (rankt[i] == size - 1) {
            k = 0;
            continue;
        }
        int j = suff_ind[rankt[i] + 1];
        while (i + k < size && j + k < size && word[i + k] == word[j + k]) k++;
        lcp[rankt[i]] = k;
    }

    ull q, tmp;
    ord[0] = size - suff_ind[0];;
    for (int i = 1; i < size; ++i) {
        ord[i] = ord[i - 1] + size - suff_ind[i] - lcp[i - 1];;
    }
    scanf("%llu", &q);
    vector<pair<int,int>> que(q,{0,0}),ans(q,{0,1});
    for (int i = 0; i < q; ++i) {
        ull tmp;
        scanf("%llu", &tmp);
        que[i].first = tmp;
        que[i].second = i;
    }
    sort(que.begin(), que.end());

    int t = 0;

    for (int i = 0; i < size; ++i) {
        while (t < q && que[t].first <= ord[i]) {
            ans[que[t].second] = {suff_ind[i], que[t].first - (i > 0 ? ord[i - 1] : 0) + lcp[i - 1]};
            t++;
        }
    }

    for (int i = 0; i < q; ++i) {
        printf("%.*s\n", ans[i].second, word + ans[i].first);
    }
    return 0;
}
