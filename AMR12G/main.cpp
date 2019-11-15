//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/AMR12G/

#include <iostream>
#include <string>
#include <fstream>
#include <set>

using namespace std;

int main(){
    int c;
    //ifstream cin ("C:\\Users\\Anton\\CLionProjects\\spoj\\AMR12G\\in.txt");

    cin >> c;

    while(c--){
        int n,m, k;
        char tmp;
        multiset<int> on_set;
        cin >> n >> m >> k;
        while(n--){
            int on = 0;
            for(int i = 0; i < m; ++i){
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
        int tot_on = 0;
        for(auto on : on_set){
            tot_on += on;
        }
        cout << tot_on << endl;
    }
    return 0;
}