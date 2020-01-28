//https://www.spoj.com/problems/BTCK/
#include <iostream>
#include <vector>
#include <fstream>
using  namespace std;

int k;
vector<int> permutation;

bool operator < (vector<int> const& a, vector<int> const& b){
    for(int i = 0; i < 10; ++i){
        if(a.at(i) < b.at(i)) {
            return true;
        }else if(a.at(i) > b.at(i)) {
            return false;
        }
    }
    return true;
}

void find_permutation(vector<int> const& input, vector<int>& elements, int step){
    if(step == 10 || permutation.size() != 0)
        return;

    int tmp = 0;

    for(int i = 0; i < 10; ++i)
        tmp += input.at(i)*elements.at(i);

    if(tmp <= k && (permutation.size() == 0 || elements < permutation))
        for(int i = 0; i < 10; ++i)
            if(permutation.size() < 10){
                permutation.push_back(elements.at(i));
            }else{
                permutation.at(i) = elements.at(i);
            }


    for(int i = step; i < 10; ++i){
        swap(elements.at(step), elements.at(i));
        find_permutation(input, elements, step + 1);
        swap(elements.at(step), elements.at(i));
    }
}

int main() {
    int cases, tmp;

    ifstream inFile ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\28587\\in.txt");

    inFile >> cases;

    for(int i = 0; i < cases; ++i){
        permutation.clear();
        vector<int> input, elements;
        for(int j = 0; j < 10; ++j){
            inFile >> tmp;
            input.push_back(tmp);
            elements.push_back(j);
        }

        inFile >> k;

        find_permutation(input, elements, 0);

        if(permutation.size() > 0){
            for(int p = 0; p < 10; ++p){
                cout << permutation.at(p);
                if(p != 9)
                    cout << " ";
            }
        } else {
            cout << "-TEST";
        }
        cout << endl;
    }

    return 0;
}