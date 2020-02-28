//
// Created by Mortiferum on 12.01.2020.
//

#include<bits/stdc++.h>

using namespace std;
typedef unsigned int ui;

const ui max_dim = 100001;
char word [max_dim];
ui suff_ind [max_dim], size;

bool smaller (ui ind_i, ui ind_j){
    return strcmp(&word[ind_i], &word[ind_j] )< 0;
}

int main() {
    scanf("%s", word);
    size = strlen(word);
    for(ui i = 0; i < size; ++i)
        suff_ind[i] = i;
    sort(suff_ind, suff_ind+size, smaller);
    for(ui i = 0; i < size; ++i)
        printf("%d\n", suff_ind[i]);
    return 0;
}
