#include <bits/stdc++.h>
using namespace std;
int t[11]={1023},j;
void dfs(int i,int c,int x,int y) {
    if(!i)for(j=10;~j;cout<<bitset<10>(t[j--]));
    else
    for (int j = 512; j; j/=2)
        if (!((c & j) | (x & (j << (10 - i))) | (y & (j << i)))) {
            t[i]=j;
            dfs(i-1, c | j, x | (j << (10 - i)), y | (j << i));
        }
}main(){dfs(10, 0, 0, 0);}