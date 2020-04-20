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
typedef long long int lli;
typedef unsigned int ui;

const ui max_dim = 50001;
char word [max_dim];
ui suff_ind [max_dim], size;

bool smaller (ui ind_i, ui ind_j){
    return strcmp(&word[ind_i], &word[ind_j] )< 0;
}

int main() {
    ui t;
    scanf("%d", &t);
    while(t--) {
        scanf("%s", word);
        size = strlen(word);
        for (ui i = 0; i < size; ++i)
            suff_ind[i] = i;
        sort(suff_ind, suff_ind + size, smaller);
        ui tot = 0;
        for (ui i = 0; i < size; ++i) {
            tot += size - suff_ind[i];
            bool sim = true;
            ui sim_c = 0, cur = suff_ind[i], cur_2 = suff_ind[i+1];
            while(sim && i != size - 1){
                if(word[cur] == word[cur_2]){
                    cur++;cur_2++; sim_c++;
                } else
                    sim = false;
            }
            tot -= sim_c;
        }
        cout << tot << "\n";
    }
    return 0;
}
