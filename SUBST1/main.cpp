#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    while(n--){
        int a,b,c,tot = 0;
        cin >> a >> b >> c;
        bool done = false;
        while(!done){
            if(b % a == 0 && c % b == 0 && a <= b && b <= c)
                break;
            if(b % c != 0){
                if (c - (c / b)*b < c - ((c / b)+1)*b){
                    tot += 1;
                    b = b - 1;
                } else {
                    tot += 1;
                    b = b + 1;
                }
            }
            if(b % a != 0){
                if (b - (b / a)*a < b - ((a / a)+1)*a){
                    tot += 1;
                    a = a - 1;
                } else {
                    tot += 1;
                    a = a + 1;
                }
            }

        }
        cout << a << " " << b << " " << c << "\n" << tot << "\n";
    }
    return 0;
}