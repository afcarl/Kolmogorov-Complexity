#include <bits/stdc++.h>
using namespace std;
int t[11]={1023},j;
void dfs(int i, int c, int x, int y) {
    if (!i)
        for (j=10;~j;cout<<bitset<10>(t[j--]));
    else
    for (int j = 9; ~j; --j)
        if (!(c & (1 << j)) && !(x & (1 << (10 + j - i))) && !(y & (1 << (i + j)))) {
            t[i] = 1<<j;
            dfs(i - 1, c | (1 << j), x | (1 << (10 + j - i)), y | (1 << (i + j)));
        }
}
int main() {
    dfs(10, 0, 0, 0);
    return 0;
}