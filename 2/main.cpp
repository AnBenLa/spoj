//https://www.spoj.com/problems/PRIME1/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

bool check_prime(int in, vector<int>const& prec_primes){
    //check if input is 1 because 1 is not a prime number
    if(in == 1)
        return false;
    //check if the input is divisible by the first few houndred primes (prime-factorisation)
    if(in > prec_primes.back()) {
        for (int prime : prec_primes) {
            if (in % prime == 0)
                return false;
        }
        //if in is nost divisible by one of the precomputed primes check for divisibility by all numbers bigger
        for (int i = prec_primes.back(); i <= sqrt((float) in); ++i) {
            if (in % i == 0)
                return false;
        }
    } else {
        //if in is lower than the biggest precomputed prime check if it is contained in our list of prec primes
        if(find(prec_primes.begin(), prec_primes.end(), in) != prec_primes.end())
            return true;
        return false;
    }
    return true;
}


int main() {
    int cases, m, n;
    vector<int> prec_primes;

    //precompute first few houndred primes
    for(int i = 2; i < 10; ++i){
        bool is_prime = true;
        for(int j = 2; j <= sqrt((float)i); ++j){
            if(i % j == 0)
                is_prime = false;
        }
        if(is_prime)
            prec_primes.push_back(i);
    }

    cin >> cases;

    for(int i = 0; i < cases; ++i){
        cin >> m >> n;
        for(int j = m; j <= n; ++j){
            if(check_prime(j, prec_primes))
                cout << j << endl;
        }
    }

    return 0;
}