#include<bits/stdc++.h>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned int ui;

ui n, char_count[26];

//implementation from: https://w...content-available-to-author-only...s.org/suffix-array-set-2-a-nlognlogn-algorithm/
typedef long long ll;
typedef vector<ll> vi;
#define maxn 300009


vector<ll> suffix_array(string& s)
{
    ll n = s.size(), N = n + 256;
    vector<ll> sa(n), ra(n);
    for(ll i = 0; i < n; i++) sa[i] = i, ra[i] = s[i];
    for(ll k = 0; k < n; k ? k *= 2 : k++)
    {
        vector<ll> nsa(sa), nra(n), cnt(N);
        for(ll i = 0; i < n; i++) nsa[i] = (nsa[i] - k + n) % n;
        for(ll i = 0; i < n; i++) cnt[ra[i]]++;
        for(ll i = 1; i < N; i++) cnt[i] += cnt[i - 1];
        for(ll i = n - 1; i >= 0; i--) sa[--cnt[ra[nsa[i]]]] = nsa[i];

        ll r = 0;
        for(ll i = 1; i < n; i++)
        {
            if(ra[sa[i]] != ra[sa[i - 1]]) r++;
            else if(ra[(sa[i] + k) % n] != ra[(sa[i - 1] + k) % n]) r++;
            nra[sa[i]] = r;
        }
        ra = nra;
    }
    return sa;
}

int main() {
    cin.sync_with_stdio(0), cin.tie(0);
    //~ freopen("in", "r", stdin);

    string str;
    cin>>str;
    n = str.size();
    str += '#';
    vi suff_ind = suffix_array(str);

    for(ui i = 0; i < n; ++i){
        //find difference between adjacent words in the suffix array
        ui cur_i = suff_ind[i], cur_j = suff_ind[i+1], diff = 0;
        bool finished = false;
        while(!finished && cur_i < n && cur_j < n) {
            if (txt[cur_i] != txt[cur_j])
                finished = true;
            else {
                diff++; cur_i++; cur_j++;
            }
        }
        //increase the count for the character
        char_count[txt[suff_ind[i]] - 'a'] += n - suff_ind[i] - diff;
    }
    for (ui i = 0; i < 26; ++i){
        printf("%d", char_count[i]);
        if(i < 25)
            printf(" ");
    }
    return 0;
}