//
// Created by Mortiferum on 12.01.2020.
//

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
typedef unsigned int ui;
typedef  unsigned short us;

ui memory[2010][2010];

void lcs(string const& a, string const& b){
    ui n = a.size(), m = b.size();
    for(ui i = 0; i <= n; ++i)
        for(ui j = 0; j <= m; ++j) {
            if (i == 0 || j == 0)
                memory[i][j] = 0;
            else
                memory[i][j] = (a[i - 1] == b[j - 1]) ? 1 + memory[i - 1][j - 1] : max(memory[i - 1][j],
                                                                                       memory[i][j - 1]);
        }
}

string find_lcs(string const& a, string const& b){
    ui i = a.size(), j = b.size();
    string res;
    while(i > 0 && j > 0){
        if(a[i-1] == b[j-1]) {
            res.insert(res.begin(), (a[i-1]));
            i--; j--;
        }else if(memory[i-1][j] > memory[i][j-1])
            i--;
        else
            j--;
    }
    return res;
}

string mix(string const& a, string const& b){
    lcs(a,b);
    string res = find_lcs(a,b);
    string mix;
    ui j = 0, k = 0;
    for(ui i = 0; i < res.size(); ++i){
        while(a[j] != res[i]) {
            mix.push_back(a[j]);
            j++;
        }
        while(b[k] != res[i]) {
            mix.push_back(b[k]);
            k++;
        }
        mix.push_back(res[i]);
        j++; k++;
    }
    for(ui i = j; i < a.size(); ++i)
        mix.push_back(a[i]);
    for(ui i = k; i < b.size(); ++i)
        mix.push_back(b[i]);
    return mix;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin ("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\ADFRUITS\\in.txt");
    string a,b;
    while(cin >> a >> b){
        cout << mix(a,b) << "\n";
    }
    return 0;
}
