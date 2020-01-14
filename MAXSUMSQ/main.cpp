//
// Created by Mortiferum on 12.01.2020.
// https://www.spoj.com/problems/MAXSUMSQ/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef unsigned int ui;
typedef long long int lli;
#define fo(i,j,n) for(i=j;i<n;i++)

pair<lli,lli> compute_max_sub_sum(vector<lli> const& elements, vector<lli>& memo, vector<lli>& memo2){
    // array to keep track of the maximum subsequence sum
    memo[0] = elements[0];
    // array to keep track of the number of subsequences starting from the largest value until now
    memo2[0] = 1;

    lli max_pos = 0, max_elem = memo[0], i;

    fo(i,1,elements.size()){
        lli tmp = elements[i] + memo[i-1];
        if(tmp > elements[i]){
            // if it makes sense to take the element an continue the subsequence do not increase the number of subsequences
            // that we have until this point
            memo[i] = tmp;
            memo2[i] = memo2[i-1];
        } else if(tmp < elements[i]){
            // if it makes more sense to start a new subsequence start it and set the number of subsequences starting
            // from this position to 1
            memo[i] = elements[i];
            memo2[i] = 1;
        } else {
            // if it makes no difference if we start a new subsequence or keep the old one increase the number of subsequences
            // which start from the last subsequence point by 1
            memo[i] = tmp;
            memo2[i] = memo2[i-1]+1;
        }
        // keep track of the maximum element
        if(memo[i] > max_elem)
            max_elem = memo[i];
    }
    lli res = 0;
    fo(i,0,elements.size()){
        if(memo[i] == max_elem)
            res += memo2[i];
    }
    return {max_elem, res};
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\MAXSUMSQ\\in.txt");
    int t,e, tmp;
    vector<lli> elements, memo, memo2;
    cin >> t;
    while(t--){
        cin >> e;
        elements.clear();
        memo.clear();
        memo2.clear();
        if(e == 1){
            cin >> tmp;
            cout << tmp << " 1\n";
            continue;
        }
        for(int i = 0; i < e; ++i){
            cin >> tmp;
            elements.push_back(tmp);
            memo.push_back(0);
            memo2.push_back(0);
        }

        auto max_sub_sum = compute_max_sub_sum(elements, memo, memo2);
        cout << max_sub_sum.first << " " << max_sub_sum.second << "\n";
    }
    return 0;
}
