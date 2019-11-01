#include <iostream>
#include <string>

using namespace std;

class Node{
    public:
        string value;
        Node* parent;
        Node* left;
        Node* right;
        friend ostream & operator << (ostream &out, Node const& node);

    Node(string value, Node* parent, Node* left, Node* right):value{value}, parent{parent}, left{left}, right{right}{};
};

ostream & operator << (ostream& out, Node const& node){
    if(node.left != nullptr) {
        out << (*node.left);
    }
    if(node.right != nullptr){
        out << (*node.right);
    }
    out << node.value;
    return out;
}

Node* compute_tree(string &input) {
    int stat = 0;
    //remove brackets
    if ((input.at(0) == '(') && (input.at(input.length() - 1) == ')')) {
        input = input.substr(1, input.length() - 2);
    }

    Node* root = new Node("", nullptr, nullptr, nullptr);
    //create tree for expression
    if(input.length() == 1) {
        root->value = input;
        return root;
    }
    for (int i = 0; i < input.length(); ++i) {
        if (input.at(i) == '(')
            stat += 1;
        if (input.at(i) == ')')
            stat -= 1;
        //find operator in the middle
        if (stat == 0) {
            bool operator_found = false;
            if (input.at(i) == '^') {
                root->value = '^';
                operator_found = true;
            }
            if (input.at(i) == '/') {
                root->value = '/';
                operator_found = true;
            }
            if (input.at(i) == '*') {
                root->value = '*';
                operator_found = true;
            }
            if (input.at(i) == '-') {
                root->value = '-';
                operator_found = true;
            }
            if (input.at(i) == '+') {
                root->value = '+';
                operator_found = true;
            }
            if(operator_found) {
                string left = input.substr(0, i);
                string right = input.substr(i + 1, input.length() - 1);
                root->left = compute_tree(left);
                root->left->parent = root;
                root->right = compute_tree(right);
                root->right->parent = root;
            }
        }
    }
    return root;
}

int main() {
    int cases;
    string expression;
    cin >> cases;
    for (int i = 0; i < cases; ++i) {
        cin >> expression;
        Node* expression_tree = compute_tree(expression);
        cout << *expression_tree << endl;
    }

    return 0;
}