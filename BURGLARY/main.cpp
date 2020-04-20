//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/BURGLARY/

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ui tot = 0, num = 0;
bool poss, mult;

void subset_sum_recursive(std::list<int>& numbers, int target, std::list<int>& partial){
    if(mult)
        return;
    int s = 0;
    for (std::list<int>::const_iterator cit = partial.begin(); cit != partial.end(); cit++){
        s += *cit;
    }
    if(s == target){
        if(poss && num != partial.size())
            mult = true;
        poss = true;
        num = partial.size();
    }
    if(s >= target)
        return;
    int n;
    for (std::list<int>::const_iterator ai = numbers.begin(); ai != numbers.end(); ai++){
        n = *ai;
        std::list<int> remaining;
        for(std::list<int>::const_iterator aj = ai; aj != numbers.end(); aj++){
            if(aj == ai)continue;
            remaining.push_back(*aj);
        }
        std::list<int> partial_rec=partial;
        partial_rec.push_back(n);
        subset_sum_recursive(remaining,target,partial_rec);
    }
}

void subset_sum(std::list<int>& numbers,int target){
    std::list<int> partial;
    subset_sum_recursive(numbers,target,partial);
}

int main() {
    ui t, n, d, tmp;
    std::list<int> left,right;

    scanf("%u", &t);

    for (ui z = 1; z <= t; ++z) {
        poss = false;
        mult = false;
        scanf("%u", &n);
        scanf("%u", &d);
        lli half = d/2;
        bool t = false;
        for (lli i = 1; i <= n; ++i) {
            scanf("%u", &tmp);
            if(tmp < d)
                t = true;
            if(tmp <= half)
                left.push_back(tmp);
            else
                right.push_back(tmp);
        }

        if(t) {
            subset_sum(left, d);
            for (auto elem : right) {
                subset_sum(left, d - elem);
            }
        }
        if (poss && !mult)
            printf("Case #%d: %d\n", z, num);
        else if (!poss)
            printf("Case #%d: IMPOSSIBLE\n", z);
        else
            printf("Case #%d: AMBIGIOUS\n", z);
        left.clear();
        right.clear();
    }
    return 0;
}