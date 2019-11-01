#include <iostream>
#include <vector>

using namespace std;

void print_vec(vector<int> const& vec){
    for(int i = 0; i < vec.size(); ++i){
        cout << vec.at(i);
    }
    cout << endl;
}

bool is_palindrome(vector<int> const& input){
    if(input.size() % 2 == 0) {
        for (int i = 0; i < input.size()/2; ++i) {
            if (input.at(i) != input.at(input.size() - 1 - i))
                return false;
        }
    } else {
        for (int i = 0; i < (input.size()-1)/2; ++i) {
            if (input.at(i) != input.at(input.size() - 1 - i))
                return false;
        }
    }
    return true;
}

void increase (vector<int>& a, int index){
    if(a.size() == 0)
        return;
    int carry = 1;
    int itt = 0;
    while(carry == 1){
        if(itt == a.size() - index){
            a.insert(a.begin(),1);
            break;
        }
        a.at(a.size() - 1 - itt - index) = (a.at(a.size() - 1 - itt - index) + 1) % 10;
        carry = 0;
        if(a.at(a.size() - 1 - itt - index) == 0)
            carry = 1;
        itt += 1;
    }
}

void next_palindrome(vector<int>& input, int index){
    if(index == input.size()/2 || index == (input.size() + 1) / 2)
        return;
    if(input.at(0 + index) == input.at(input.size() - 1 - index)){
        next_palindrome(input, index + 1);
    } else {
        if(input.at(0 + index) < input.at(input.size() - 1 - index)) {
            increase(input, index + 1);
        }
        input.at(input.size() - 1 - index) = input.at(0 + index);
        next_palindrome(input, index);
        if(input.size() == 2){
            while(!is_palindrome(input)) {
                increase(input, index);
            }
        }
        input.at(input.size() - 1) = input.at(0);
    }
    return;
}

int main() {
    int cases;
    char tmp;
    cin >> cases;

    for(int i = 0; i < cases; ++i){
        vector<int> input_vec;
        input_vec.reserve(1000000);
        if(cin.peek() == '\n')
            cin.ignore(1);
        while ((cin.peek() != '\n') && (cin >> tmp)){
            input_vec.push_back(tmp - 48);
        }
        if(is_palindrome(input_vec))
            increase(input_vec,0);
        next_palindrome(input_vec, 0);
        print_vec(input_vec);
    }
    return 0;
}