//
// Created by Mortiferum on 12.01.2020.
// https://www.spoj.com/problems/MAXSUMSU/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef unsigned int ui;

int compute_max_sub_sum(vector<int> const& elements, vector<int>& memo){
    //vector<int> subsequence;
    memo[0] = elements[0];
    int max_pos = 0, max_elem = memo[0], res = 0;
    for(int i = 1; i < elements.size(); ++i){
        memo[i] = max(elements[i] + memo[i-1], elements[i]);
        if(memo[i] > max_elem){
            max_elem = memo[i];
            max_pos = i;
        }
    }
    return max_elem;
    /*
    for(int i = max_pos; res != max_elem ;i--){
        res += elements[i];
        subsequence.insert(subsequence.begin(), elements[i]);
    }
    return subsequence;
     */
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\MAXSUMSU\\in.txt");
    int t,e, tmp;
    vector<int> elements, memo;
    cin >> t;
    while(t--){
        cin >> e;
        elements.clear();
        memo.clear();
        for(int i = 0; i < e; ++i){
            cin >> tmp;
            elements.push_back(tmp);
            memo.push_back(0);
        }
        int max_sub_sum = compute_max_sub_sum(elements, memo);
        cout << max_sub_sum << "\n";
    }
    return 0;
}
