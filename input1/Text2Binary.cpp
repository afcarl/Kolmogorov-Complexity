#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    ifstream textIn(argv[1]);
    ofstream outBinary(argv[2], ios::binary);
    int cnt = 0;
    char c;
    char o = 0;
    while (textIn >> c) {
        o = o << 1 | (c == '1');
        ++cnt;
        if (cnt == 8) {
            outBinary.write(&o, 1);
            o = 0;
            cnt = 0;
        }
    }
    return 0;
}