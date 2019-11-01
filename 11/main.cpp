#include <iostream>

using namespace std;

int main() {
    int c,t,b,n;
    cin >> c;
    for(int i = 0; i < c; ++i){
        cin >> t;
        b = 5;
        n = 0;
        while(b <= t) {
            n += t / b;
            b *= 5;
        }
        cout << n << endl;
    }
    return 0;
}