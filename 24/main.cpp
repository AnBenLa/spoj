#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> x(unsigned long long int a){
    vector<int> c;
    int l;
    while(a > 0){
        l = a % 10;
        c.push_back(l);
        a = (a-l) / 10;
    }
    reverse(c.begin(), c.end());
    return c;
}

vector<int> operator+(vector<int> const& a, vector<int> const& b){
    vector<int> c;
    int la, lb, t, d, r, m, l;
    la = a.size();
    lb = b.size();
    d = 0;
    if(la < lb) {
        r = la;
        m = lb;
    } else {
        r = lb;
        m = la;
    }
    for(int i = 1; i <= r; ++i){
        t = a.at(a.size() - i) + b.at(b.size() - i);
        l = ((t % 10) + d) % 10;
        c.push_back(l);
        d = (t + d) / 10;
    }
    if(d > 0 && (la == lb)) {
        c.push_back(d);
        reverse(c.begin(), c.end());
        return c;
    }
    for(int j = r; j < m; ++j){
        if(la < lb) {
            t = b.at(b.size() - 1 - j) + d;
        } else {
            t = a.at(a.size() - 1 - j) + d;
        }
        c.push_back(t % 10);
        d = t / 10;
    }
    if(d > 0){
        c.push_back(d);
    }
    reverse(c.begin(), c.end());
    return c;
}

vector<int> operator*(vector<int> const& a, int b){
    vector<int> c;
    c.push_back(0);
    for(int i = 0; i < b; i++){
        c = c + a;
    }
    return c;
}

vector<int> operator*(vector<int> const& a, vector<int> const& b){
    vector<int> c;
    c.push_back(0);
    for(int i = 0; i < b.size(); ++i){
        auto t = a * b.at(b.size() - 1 - i);
        for(int j = 0; j < i; ++j)
            t.push_back(0);
        c = c + t;
    }
    return c;
}

int main() {
    int c, t;
    vector<vector<int>> f;
    vector<int> z;
    z.push_back(1);
    f.push_back(z);
    cin >> c;
    int prev = 0;
    int u = 1024/5 + 1024/25 + 1024/125 + 1024/625;

    for(int i = 0; i < c; ++i){
        //cin >> t;
        t = (i+1)*5;
        for(int j = f.size(); j <= t; ++j) {
            f.push_back(f.back() * x(j + 1));
        }
        int count = 0;
        for(int p = 0; p < f.at(t - 1).size(); ++p)
            if(f.at(t - 1).at(f.at(t-1).size() - 1 - p) == 0) {
                count += 1;
            } else {
                break;
            }
        cout << count - prev << ", ";
        prev = count;
    }
    return 0;
}