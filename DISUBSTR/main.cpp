//
// Created by Mortiferum on 12.01.2020.
//

#include<bits/stdc++.h>

using namespace std;
typedef unsigned int ui;

struct node;
const ui char_num = 60;
ui result, size;
node* root;
char tmp [1001];

struct node{
    public:
        node* child[char_num]{nullptr};
};

void del (node* cur){
    for(ui i = 0; i < char_num; ++i) {
        if (cur->child[i] != nullptr)
            del(cur->child[i]);
    }
    delete(cur);
}

int main() {
    ui n;
    scanf("%d", &n);
    while(n--) {
        result = 0;
        root = new node;
        scanf("%s", tmp);
        size = strlen(tmp);
        for(ui i = 0; i < size; ++i){
            node *current_node = root;
            for(ui j = i; j < size; ++j) {
                    if (current_node->child[tmp[j] - '!'] == nullptr) {
                        current_node->child[tmp[j] - '!'] = new node;
                        result++;
                    }
                    current_node = current_node->child[tmp[j] - '!'];
                }
            tmp[i] = '\0';
        }
        cout << result << "\n";
        del(root);
    }
    return 0;
}
