#include <iostream>
#include <math.h>
using namespace std;

int main() {
    long long int n, a, pre[100001];
    for(long long int i = 0; i < 100001; ++i)
        pre[i] = i*i;
    cin >> n;
    while(n--){
        cin >> a;
        bool possible = false;
        float sqa = sqrt(a);
        long long int i = 0, j = sqrt(a);
        while(i <= j){
            long long int p = pre[i] + pre[j];
            if(p == a) {
                possible = true;
                break;
            }
            if(p > a){
                j--;
            } else {
                i++;
            }
        }
        if(possible)
            cout << "Yes\n";
        else
            cout << "No\n";
    }
    return 0;
}