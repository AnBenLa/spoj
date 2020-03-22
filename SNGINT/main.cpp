//
// Created by Mortiferum on 08.12.2019.
//
#include<bits/stdc++.h>
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
typedef unsigned long long ull;
typedef long long int lli;
typedef unsigned int ui;

int main() {
    ui t, tmp;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&tmp);
        if(tmp == 0){
            printf("%d\n", 10);
        } else if(tmp == 1){
            printf("%d\n",1);
        } else {
            ui res = 0, step = 0; bool finished = false;
            while(!finished){
                bool pos = false;
                for(ui i = 9; i > 1; --i){
                    if(tmp % i == 0) {
                        res += i * pow(10,step);
                        step++;pos = true;
                        tmp /= i;
                        break;
                    }
                }
                if(!pos){
                    res = -1;
                    break;
                }
                if(tmp == 1)
                    finished = true;
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
