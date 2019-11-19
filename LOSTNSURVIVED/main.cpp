//
// Created by Anton on 13.11.2019.
// https://www.spoj.com/problems/LOSTNSURVIVED/

#include <vector>
#include <unordered_map>

using namespace std;

int n,q,a,b,root,tmp,k = 0, ma_r = 0, mi_r = 0;
unordered_map<int, int> pers_m;
vector<int> passed_notes;

//https://www.geeksforgeeks.org/fast-io-for-competitive-programming/
void fastscan(int &number){
    register int c;
    number = 0;
    c = getchar();
    for (; (c>47 && c<58); c=getchar())
        number = number *10 + c - 48;
}

//https://www.geeksforgeeks.org/common-mistakes-avoided-competitive-programming-c-beginners/
void fast_output(int x, int mode)
{
    char a[20];
    int i=0, j;
    a[0] = '0';
    if (x==0)
        putchar('0');
    while (x){
        a[i++] = x%10 + 48;
        x /= 10;
    }
    for (j=i-1; j>=0; j--)
        putchar(a[j]);
    if (mode == 0)
        putchar('\n');
    else putchar(' ');
}

int find_root(int b){
    passed_notes.clear();
    //finding root node of b in pers
    while(pers_m[b] > 0){
        passed_notes.push_back(b);
        b = pers_m[b];
    }
    //path compression
    for(auto passed : passed_notes){
        pers_m[passed] = b;
    }
    //set index from root node with max and min elements
    if(ma_r == 0 || pers_m[b] < pers_m[ma_r])
        ma_r = b;
    if(mi_r == 0 || pers_m[b] > pers_m[mi_r])
        mi_r = b;
    return b;
}

int main(){
    fastscan(n);
    fastscan(q);

    while(q--){
        fastscan(a);
        fastscan(b);
        if(pers_m.find(a) == pers_m.end() && pers_m.find(b) == pers_m.end()){
            //if a and b dont exists yet add them and set a as root of b
            root = a;
            pers_m[root] = -2;
            pers_m[b] = a;
            k += 2;
        } else if(pers_m.find(a) == pers_m.end()){
            //if b exists set the root of a to b
            pers_m[a] = b;
            root = find_root(b);
            pers_m[root] -= 1;
            k += 1;
        } else if(pers_m.find(b) == pers_m.end()){
            //if a exists set the root of b to a
            pers_m[b] = a;
            root = find_root(a);
            pers_m[root] -= 1;
            k += 1;
        } else {
            //if both exists check if they have the same root
            root = find_root(a);
            int root_2 = find_root(b);
            //if the roots are different merge the two trees
            if(root != root_2){
                tmp = pers_m[root_2];
                pers_m[root_2] = root;
                pers_m[root] += tmp;
                find_root(b);
            }
        }
        find_root(root);
        if(k < n)
            fast_output(-pers_m[ma_r] - 1, 0);
        else if(-pers_m[ma_r] != n)
            fast_output(-pers_m[ma_r] + pers_m[mi_r], 0);
        else
            fast_output(0, 0);
    }
    return 0;
}