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
    node* child[26]{nullptr};
    bool isWord = false;
    ui word_count = 0;
};

ui n,q;
string tmp;


void add_word(string const& word, node* root){
    node* current_node = root;
    for(char c : word){
        current_node->word_count += 1;
        node* child = current_node->child[c-'a'];
        if(child == nullptr)
            current_node->child[c-'a'] = new node;
        current_node =  current_node->child[c-'a'];
    }
    current_node->isWord = true;
    current_node->word_count += 1;
}

int count_prefix(string const& word, node* root){
    node* current_node = root;
    for(char c : word){
        node* child = current_node->child[c-'a'];
        if(child == nullptr)
            return 0;
        current_node =  current_node->child[c-'a'];
    }
    return current_node->word_count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\ADAINDEX\\in.txt");
    cin >> n >> q;
    node* root = new node;
    while(n--) {
        cin >> tmp;
        add_word(tmp,root);
    }
    while(q--){
        cin >> tmp;
        cout << count_prefix(tmp,root) << "\n";
    }
    return 0;
}
