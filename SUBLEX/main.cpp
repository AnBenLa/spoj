//
// Created by Mortiferum on 12.01.2020.
//

#include<bits/stdc++.h>

using namespace std;
typedef unsigned int ui;

const ui max_dim = 100001;
char word [max_dim];
ui suff_ind [max_dim], diff[max_dim], size, n, tmp;

bool smaller (ui ind_i, ui ind_j){
    return strcmp(&word[ind_i], &word[ind_j] )< 0;
}

void find_diff(ui i, ui j){
    ui cur_i = suff_ind[i], cur_j = suff_ind[j], result = 0;
    while(cur_i < size && cur_j < size) {
        if (word[cur_i] != word[cur_j]) {
            diff[i] = result;
            return;
        } else {
            result++;
            cur_i++;
            cur_j++;
        }
    }
    diff[i] = result;
}

int main() {
    scanf("%s", word);
    scanf("%d",n);
    size = strlen(word);
    for(ui i = 0; i < size; ++i)
        suff_ind[i] = i;
    sort(suff_ind, suff_ind+size, smaller);
    for(ui i = 0; i < size; ++i)
        find_diff(i,i+1);
    while(n--){
        scanf("%d",tmp);

    }
    return 0;
}
