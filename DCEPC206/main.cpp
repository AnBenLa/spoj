//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/DCEPC206/

#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <unordered_map>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ui t,n,l,tmp;
ulli sum;
ulli stair[100001];
ui elem[100001];
ui tmp_a[100001];
unordered_map<ui,ui> hm;

lli prev(lli ind){
    return (ind & (ind + 1))-1;
}

lli getSum(lli ind){
    lli res = 0;
    while(ind >= 0){
        res += stair[ind];
        ind = prev(ind);
    }
    return res;
}

void increment(){
    tmp = l;
    while(l < 100001){
        stair[l] += hm[tmp];
        l |= l+1;
    }
    l = tmp;
}

ui find_v(ui a){
    ui start = 0, end = n;
    while(start <= end){
        ui mid = (start + end) >> 1;
        if(tmp_a[mid] == a)
            return mid;
        else if(tmp_a[mid] > a)
            end = mid - 1;
        else
            start = mid + 1;
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\DCEPC206\\in.txt");

    cin >> t;
    while(t--){
        cin >> n;
        sum = 0;
        for(ui i = 0; i < n; ++i){
            stair[i] = 0;
        }

        for(ui i = 0; i < n; ++i){
            cin >> tmp;
            elem[i] = tmp;
            tmp_a[i] = tmp;
        }

        sort(tmp_a, tmp_a + n);

        for (ui i = 0; i < n; ++i) {
            tmp = find_v(elem[i]);
            hm[tmp + 1] = elem[i];
            elem[i] = tmp + 1;
        }

        for(ui i = 0; i < n; ++i){
            l = elem[i];
            increment();
            sum += getSum(l-1);
        }
        cout << sum << "\n";
    }

    return 0;
}