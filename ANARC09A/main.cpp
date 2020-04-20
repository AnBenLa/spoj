//
// Created by Mortiferum on 08.12.2019.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>

using namespace std;
typedef unsigned short us;
typedef unsigned long long int ulli;
typedef long long int lli;
typedef unsigned int ui;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    //ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\ANARC09A\\in.txt");
    string tmp;
    bool finished = false;
    ui ind = 1;
    while(!finished){
        cin >> tmp;
        if(tmp[0] == '-')
            finished = true;
        else{
            ui op = 0, cl = 0, sw = 0;
            for(ui i = 0; i < tmp.length(); ++i){
                if(tmp[i] == '{') {
                    op++;
                } else {
                    if(op > 0) {
                        op--;
                    } else {
                        sw++;
                        op++;
                    }
                }
            }
            cout << ind << ". " <<  sw  + op / 2<< "\n";
            ind++;
        }
    }
    return 0;
}
