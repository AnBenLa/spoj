//https://www.spoj.com/problems/TEST/
#include <iostream>
using namespace std;

int main() {
    int num;
    bool solution = false;
    while(!solution){
        cin >> num;
        if(num == 42)
            solution = true;
        else
            cout << num << endl;
    }
    return 0;
}