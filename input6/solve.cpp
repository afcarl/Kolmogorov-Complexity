#include<cstdio>
int i, j;
int main() {
    for(; i<4096; i++)
        for(j = 13; --j; putchar((i>>1^i)>>12-j&1^48));
}
