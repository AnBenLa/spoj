//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/TULIPNUM/

#include <iostream>
#include <unordered_map>
#include <fstream>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ui n,q,t,tmp,tmp_o, ind;
lli sum,l,r;
ui arr[100002];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\TULIPNUM\\in.txt");

    cin >> t;
    while(t--) {
        cin >> n >> q;
        tmp_o = 0;
        ind = 0;
        for (ui i = 1; i <= n; ++i) {
            cin >> tmp;
            if(tmp != tmp_o){
                ind += 1;
            }
            arr[i] = ind;
            tmp_o = tmp;
        }

        while (q--) {
            cin >> l >> r;
            cout << arr[r]-arr[l] + 1<< "\n";
        }
    }
    return 0;
}