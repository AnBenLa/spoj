#include <set>
#include <fstream>
#include <iostream>

using namespace std;
typedef unsigned short us;
typedef unsigned int ui;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream cin("C:\\Users\\Anton\\CLionProjects\\spoj\\LINES\\in.txt");
    us n;
    short x[201], y[201];
    set<float> s;

    while (true) {
        s.clear();
        cin >> n;
        if (n == 0)
            return 0;
        for (us i = 0; i < n; ++i)
            cin >> x[i] >> y[i];
        for (us i = 0; i < n; ++i)
            for (us j = i + 1; j < n; ++j) {
                if (x[j] - x[i] == 0)
                    s.insert(99999.0f);
                else
                    s.insert((float)(y[j] - y[i]) / (float)(x[j] - x[i]));
            }
        cout << s.size() << "\n";
    }
}