#include<bits/stdc++.h>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned int ui;

const ui max_dim = 300010;
char txt[max_dim];
long long suff_ind[max_dim], n, char_count[26], longPrefix[max_dim], suffixInverse[max_dim];

//implementation of the suffix array creation from: https://www.geeksforgeeks.org/suffix-array-set-2-a-nlognlogn-algorithm/
struct suffix {
    int index, rank[2];
};

int cmp(struct suffix a, struct suffix b) {
    return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) :
           (a.rank[0] < b.rank[0] ? 1 : 0);
}

void buildSuffixArray() {
    struct suffix suffixes[n];
    for (int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i + 1) < n) ? (txt[i + 1] - 'a') : -1;
    }
    sort(suffixes, suffixes + n, cmp);
    int ind[n];
    for (int k = 4; k < 2 * n; k = k * 2) {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; i++) {
            if (suffixes[i].rank[0] == prev_rank &&
                suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            } else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }
        for (int i = 0; i < n; i++) {
            int nextindex = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextindex < n) ? suffixes[ind[nextindex]].rank[0] : -1;
        }
        sort(suffixes, suffixes + n, cmp);
    }
    for (int i = 0; i < n; i++)
        suff_ind[i] = suffixes[i].index;
}

//implementation for the lcp construction from: https://www.tutorialspoint.com/kasai-s-Algorithm
void buildLCP() {
    for (int i = 0; i < n; i++)
        suffixInverse[suff_ind[i]] = i;    //fill values of inverse Suffix list
    int k = 0;
    for (int i = 0; i < n; i++) {     //for all suffix in main string
        if (suffixInverse[i] == n - 1) {    //when suffix at position (n-1)
            k = 0;
            continue;
        }

        int j = suff_ind[suffixInverse[i] + 1];    //nest string of suffix list
        while (i + k < n && j + k < n && txt[i + k] == txt[j + k]) //start from kth index
            k++;
        longPrefix[suffixInverse[i]] = k;    // prefix for the current suffix.
        if (k > 0)
            k--;    //remofe first character of string
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> txt;
    n = strlen(txt);
    buildSuffixArray();
    buildLCP();

    for (ui i = 0; i < n; ++i) {
        if (i > 0)
            char_count[txt[suff_ind[i]] - 'a'] += n - suff_ind[i] - longPrefix[i - 1];
        else
            char_count[txt[suff_ind[i]] - 'a'] += n - suff_ind[i];
    }

    for (ui i = 0; i < 26; ++i) {
        cout << char_count[i];
        if (i < 25)
            cout << " ";
    }

    return 0;
}
