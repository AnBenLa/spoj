#include <iostream>
using namespace std;

int reverse(int in){
    int out = 0;
    while(in > 0){
        out = out + (in % 10);
        out *= 10;
        in = (in - (in%10))/10;
    }
    return out/10;
}

int main() {
    int a, b, cases;
    cin >> cases;

    for(int i = 0; i < cases; ++i){
        cin >> a >> b;
        cout << reverse(reverse(a) + reverse(b)) << endl;
    }
    return 0;
}