//
// Created by Anton on 27.11.2019.
//

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

ui n,q,t,tmp;
lli sum,l,r;
ui arr[100001];
unordered_map<ui,bool> num;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream cin ("C:\\Users\\Anton\\CLionProjects\\spoj\\TULIPNUM\\in.txt");

    cin >> t;
    while(t--) {
        cin >> n >> q;
        num.clear();

        for (ui i = 1; i <= n; ++i) {
            cin >> tmp;
            arr[i] = tmp;
            num[tmp] = true;
        }

        while (q--) {
            cin >> l >> r;
            sum = 0;
            for(ulli k = l; k <= r; ++k){
                if(num[k])
                    sum += 1;
            }
            cout << sum << "\n";
        }
    }
    return 0;
}