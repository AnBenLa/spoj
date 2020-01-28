//
// Created by Mortiferum on 12.01.2020.
//

#include <stdio.h>

typedef unsigned int ui;
typedef unsigned short us;

ui adj[12][12], all_visited, m, n;
int memory[3000][3000], f[3000][3000];

ui tsp(ui mask, ui pos){
    if(mask == all_visited)
        return adj[pos][0];
    if(f[mask][pos] != -1)
        return f[mask][pos];
    ui min = 2147483647;
    for(ui c = 0; c < m + 1; ++c){
        if((mask & (1 << c)) == 0){
            ui tmp = adj[pos][c] + tsp(mask | (1<<c), c);
            if(tmp < min)
                min = tmp;
        }
    }
    f[mask][pos] = min;
    return min;
}

int cpow(int base, ui exponent){
    int result = 1;
    for (; exponent>0; exponent--){
        result = result * base;
    }
    return result;
}

int main() {
    //ifstream cin("C:\\Users\\Mortiferum\\CLionProjects\\spoj\\PESADA04\\in.txt");
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &m);
        for (ui i = 0; i < m + 1; ++i) {
            for (ui j = 0; j < m + 1; ++j) {
                if (i == j)
                    adj[i][j] = 0;
                else{
                    ui tmp = 0;
                    scanf("%d", &tmp);
                    adj[i][j] = tmp;
                }
            }
        }
        ui max_size = cpow(2, m+1);
        for(ui i = 0; i < max_size; i++)
            for(ui j = 0; j < m+1; j++)
                f[i][j] = -1;
        all_visited = max_size - 1;
        printf("%d\n", tsp(1,0));
    }
    return 0;
}
