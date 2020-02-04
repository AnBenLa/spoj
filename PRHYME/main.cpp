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
    node* father{nullptr};
    char letter = 0;
    vector<ui> dic_ind{};
    node* child[26]{nullptr};
    bool isWord = false;
    ui word_count = 0;
};

ui n,q;
string tmp;
vector<string> dictionary;


void add_word(string const& word, node* root, ui i){
    node* current_node = root;
    for(char c : word){
        if(c == '\r')
            continue;
        current_node->dic_ind.push_back(i);
        current_node->word_count += 1;
        node* child = current_node->child[c-'a'];
        if(child == nullptr)
            current_node->child[c - 'a'] = new node{current_node, c};
        current_node =  current_node->child[c-'a'];
    }
    current_node->dic_ind.push_back(i);
    current_node->isWord = true;
    current_node->word_count += 1;
}

bool operator < (string const& a, string const& b){
    string s = a, l = b;
    bool sw = false;
    if(a.length() > b.length()){
        s = b;
        l = a;
        sw = true;
    }
    for(ui i = 0; i < s.length(); ++i){
        if(s[i] < l[i]) {
            if(!sw)
                return true;
            else
                return false;
        }
        else if(s[i] > l[i]) {
            if(!sw)
                return false;
            else
                return true;
        }
    }
    return true;
};

string rhyme(string& word, node* root){
    node* current_node = root;
    node* prev_node;
    //go to the end of the reversed word in the trie
    for(char c : word){
        if(c == '\r')
            continue;
        current_node =  current_node->child[c-'a'];
    }
    //find the node where the words with the longest suffix are stored
    if(current_node == nullptr)
        current_node = root;
    while(current_node->word_count == 1){
        prev_node = current_node;
        current_node = current_node->father;
    }
    //for every word with the same prefix
    reverse(word.begin(),word.end());
    string current_small;
    for(ui i : current_node->dic_ind){
        if(dictionary[i] != word && (current_small.empty() || dictionary[i] < current_small)){
            current_small = dictionary[i];
        }
    }
    return current_small;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\PRHYME\\in-2.txt");
    node* root = new node;
    getline(cin, tmp);
    ui i = 0;
    while(!tmp.empty() && tmp != "\r"){
        dictionary.push_back(tmp);
        reverse(tmp.begin(),tmp.end());
        add_word(tmp,root, i);
        getline(cin, tmp);
        i++;
    };
    while(getline(cin, tmp)){
        reverse(tmp.begin(),tmp.end());
        cout << rhyme(tmp,root) << "\n";
    }
    return 0;
}
