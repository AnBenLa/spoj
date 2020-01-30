//
// Created by Mortiferum on 12.01.2020.
// following: https://cp-algorithms.com/string/suffix-automaton.html

#include <iostream>
#include <fstream>
#include <algorithm>
#include<bits/stdc++.h>
using namespace std;
typedef unsigned int ui;
typedef  unsigned short us;

struct state{
    int length, link;
    map<char, int> next;
};

ui weight[1001], price[1001], max_weight, enu;
char a [250001],b[250001];
state automaton[250001 * 2];
int size, last;

void automaton_init(){
    automaton[0].length = 0;
    automaton[0].link = -1;
    size++;
    last = 0;
}

void extend_automaton(char c){
    int current = size++;
    //update minimal length
    automaton[current].length = automaton[last].length + 1;
    int p = last;
    //if no transition using c or not in the final position
    while(p != -1 && !automaton[p].next.count(c)){
        automaton[p].next[c] = current;
        p = automaton[p].link;
    }
    if(p == -1)
        automaton[current].link = 0;
    else{
        int q = automaton[p].next[c];
        if(automaton[p].length + 1 == automaton[q].length)
            automaton[current].link = q;
        else{
            //clone the equivalence class path
            int clone = size++;
            automaton[clone] = {automaton[p].length + 1, automaton[q].link, automaton[q].next};
            while(p != -1 && automaton[p].next[c] == q){
                automaton[p].next[c] = clone;
                p = automaton[p].link;
            }
            automaton[q].link = automaton[current].link = clone;
        }
    }
    last = current;
}

int lcs(){
    automaton_init();
    int v = 0, l = 0, best = 0, bestpos = 0, i = 0;
    while(a[i] != 0){
        extend_automaton(a[i]);
        i++;
    }
    i = 0;
    while(b[i] != 0){
        while(v && !automaton[v].next.count(b[i])){
            v = automaton[v].link;
            l = automaton[v].length;
        }
        if(automaton[v].next.count(b[i])){
            v = automaton[v].next[b[i]];
            l++;
        }
        if(l > best){
            best = l;
            bestpos = i;
        }
        i++;
    }
    //string result = "";
    //for(ui k = 0; k < best; ++k)
    //    result = result + b[bestpos - best + k + 1];
    return best;
}

int main() {
    scanf("%s\n%s", &a, &b);
    printf("%d\n",lcs());
    return 0;
}
