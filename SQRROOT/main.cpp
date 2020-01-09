//
// Created by Anton on 09.01.2020.
// https://www.spoj.com/problems/SQRROOT/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned short us;

vector<us> operator+(vector<us> const& a, vector<us> const& b){
    vector<us> c;
    us la, lb, t, d, r, m, l;
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

vector<us> operator*(vector<us> const &a, us b) {
    vector<us> c;
    c.push_back(0);
    for (int i = 0; i < b; i++) {
        c = c + a;
    }
    return c;
}

vector<us> operator*(vector<us> const &a, vector<us> const &b) {
    vector<us> c;
    c.push_back(0);
    for (int i = 0; i < b.size(); ++i) {
        auto t = a * b.at(b.size() - 1 - i);
        for (int j = 0; j < i; ++j)
            t.push_back(0);
        c = c + t;
    }
    return c;
}

vector<us> operator ^(vector<us> const& a, unsigned int b){
    vector<us> result{1};
    while(b--){
        result*a;
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\CAPCITY\\in.txt");
    us t, tmp;
    vector<us> num;
    cin >> t;
    while (t--) {
        num.clear();
        //read input to vector
        if (cin.peek() == '\n')
            cin.ignore(1);
        while ((cin.peek() != '\n') && (cin.peek() > 47) && (cin >> tmp)) {
            num.push_back(tmp - 48);
        }
        vector<us> guess;
        vector<us> tmp_res = guess^2;
        while (tmp_res != num){
            if(tmp_res > num){
                decrease_guess();
            } else {
                increase_guess();
            }
        }
        cout << guess << "\n";
    }
    return 0;
}
