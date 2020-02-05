//
// Created by Mortiferum on 12.01.2020.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include<bits/stdc++.h>
#include <string>
using namespace std;
typedef unsigned int ui;
typedef  unsigned short us;

struct node{
    node* child[10]{nullptr};
    bool isWord = false;
    ui word_count = 0;
};

ui n,q;
string tmp;


bool add_word(string const& word, node* root){
    node* current_node = root;
    for(char c : word){
        current_node->word_count += 1;
        node* child = current_node->child[c-'0'];
        if(child == nullptr)
            current_node->child[c-'0'] = new node;
        current_node =  current_node->child[c-'0'];
        if(current_node->isWord)
            return false;
    }
    current_node->isWord = true;
    if(current_node->word_count > 0)
        return  false;
    current_node->word_count += 1;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\PHONELST\\in.txt");
    cin >> n;
    while(n--) {
        node* root = new node;
        cin >> q;
        bool possible = true;
        while(q--){
            cin >> tmp;
            bool add_num = add_word(tmp,root);
            if(!add_num) {
                possible = false;
            }
        }
        if(possible)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}
