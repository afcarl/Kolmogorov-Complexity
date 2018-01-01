#include <bits/stdc++.h>
using namespace std;
int t[11];
void dfs(int i, int c, int x, int y) {
    if (i > 9) {
        for (int j = 0; j < 11; ++j)
            cout << bitset<10>(t[j]);
        return ;
    }
    for (int j = 0; j < 10; ++j) {
        if (!(c & (1 << j)) && !(x & (1 << (10 + j - i))) && !(y & (1 << (i + j)))) {
            t[i] = 1<<10-j-1;
            dfs(i + 1, c | (1 << j), x | (1 << (10 + j - i)), y | (1 << (i + j)));
        }
    }
}
int main() {
    t[10] = (1<<10)-1;
    dfs(0, 0, 0, 0);
    return 0;
}