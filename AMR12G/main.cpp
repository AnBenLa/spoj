//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/AMR12G/

#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;
#define fo(i,j,n) for(i=j;i<n;i++);
typedef multiset<int> mi;

int main(){
    int c;
    cin >> c;

    while(c--){
        int n,m, k, tot_on = 0,i;
        char tmp;
        mi on_set;
        cin >> n >> m >> k;
        while(n--){
            int on = 0;
            fo(i,0,m){
                cin >> tmp;
                if(tmp == '*')
                    on += 1;
            }
            on_set.insert(on);
        }
        while(k--){
            int tmp_on = *on_set.begin();
            on_set.erase(on_set.begin());
            on_set.insert(m- tmp_on);
        }
        for(auto on : on_set)
            tot_on += on;
        cout << tot_on << endl;
    }
    return 0;
}