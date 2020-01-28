//
// Created by Mortiferum on 12.01.2020.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef  unsigned short us;

ui weight[1001], price[1001], max_weight, enu;

ui unb_knap(){
    ui memory[max_weight + 1];
    memset(memory, 0, sizeof memory);

    for(ui i = 0; i <= max_weight; i++)
        for(ui j = 0; j < enu; ++j)
            if(weight[j] <= i)
                memory[i] = max(memory[i], memory[i - weight[j]] + price[j]);
    return memory[max_weight];
}

int main() {
    ui n;
    scanf("%d", &n);
    while(n--){
        scanf("%d %d", &max_weight, &enu);
        for(ui i = 0; i < enu; ++i)
            scanf("%d", weight + i);
        for(ui i = 0; i < enu; ++i)
            scanf("%d", price + i);
        cout << unb_knap() << "\n";
    }
    return 0;
}
