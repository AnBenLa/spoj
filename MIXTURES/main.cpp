//
// Created by Mortiferum on 12.01.2020.
//

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef unsigned int ui;
typedef  unsigned short us;

us mixtures [101], sum[101][101];
ui smoke[101][101];

int mcm(us size){
    for(us i = 1; i < size; ++i ){
        smoke[i][i] = 0;
    }
    for(us L = 2; L < size; ++L){
        for(us i = 1; i < size - L + 1; ++i){
            int j = i + L - 1;
            int min = 2147483647;
            for(int k = i; k <= j - 1; ++k){
                int tmp_smoke = 2147483647;
                if(k == i)
                    tmp_smoke = sum[k+1][j] * mixtures[i];
                else if(k+1 == j)
                    tmp_smoke = mixtures[j] * sum[i][k];
                else
                    tmp_smoke = sum[i][k] * sum[k+1][j];
                int sm_i_k = smoke[i][k];
                int sm_k_1_j = smoke[k+1][j];
                int val = sm_i_k + tmp_smoke + sm_k_1_j;
                if(val < min){
                    min = val;
                }
            }
            smoke[i][j] = min;
        }
    }
    return smoke[1][size-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin ("C:\\Users\\Anton\\CLionProjects\\spoj\\MIXTURES\\in.txt");
    us n, tmp;
    while(cin >> n){
        for(us i = 1; i <= n; ++i){
            cin >> mixtures[i];
        }
        mixtures[n+1] = 1;

        for(us i = 1; i <= n; ++i){
            us s = 0;
            for(us k = i; k <= n; ++k){
                s += mixtures[k];
                sum[i][k] = s % 100;
            }
        }

        if(n > 1)
            cout << mcm(n+1) << "\n";
        else
            cout << "0\n";

        for(us i = 1; i <= n; ++i){
            mixtures[i] = 0;
            for(us j = 1; j <= n; ++j) {
                smoke[i][j] = 0;
            }
        }
    }
    return 0;
}
