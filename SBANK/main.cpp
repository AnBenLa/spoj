//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/SBANK/

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <map>

using namespace std;

int main(){
    int c;
    //ifstream cin ("C:\\Users\\Anton\\CLionProjects\\spoj\\SBANK\\in.txt");

    cin >> c;


    while(c--) {
        map<string, int> num_map;
        set<string> num_set;
        int n = 0;
        char num[31];
        cin >> n;
        while(n--) {
            scanf("\n%[^\n]s", num);
            num_set.insert(num);
            num_map[num]++;
        }
        for(auto elem : num_set){
            cout << elem << num_map[elem] << endl;
        }
        cout << endl;
    }
    return 0;
}