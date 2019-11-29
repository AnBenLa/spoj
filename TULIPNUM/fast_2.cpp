//
// Created by Anton on 18.11.2019.
// https://www.spoj.com/problems/TULIPNUM/

#include <iostream>
#include <fstream>

#define ui unsigned int
#define lli long long int
#define ulli unsigned long long int

using namespace std;

ulli l,r,n,q,t,tmp,tmp_o, ind;;
ui arr[100002];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin ("C:\\Users\\Anton\\CLionProjects\\spoj\\TULIPNUM\\in.txt");

    cin >> t;
    for(ui k = 1; k <= t; ++k) {
        cin >> n >> q;
        cin >> tmp_o;
        arr[1] = 1;
        ind = 1;
        for (ui i = 2; i <= n; ++i) {
            cin >> tmp;
            if(tmp != tmp_o){
                ind += 1;
            }
            arr[i] = ind;
            tmp_o = tmp;
        }

        cout << "Case " << k << ":" << "\n";
        while (q--) {
            cin >> l >> r;
            cout << arr[r]-arr[l] + 1 << "\n";
        }
    }
    return 0;
}