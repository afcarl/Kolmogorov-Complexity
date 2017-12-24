#include <bits/stdc++.h>
using namespace std;
const int N = 1e6;
char buf[N];
int buf_size, cur;

typedef unsigned long long ull;
const ull MAXC = 65535;
const ull QUAR = 16384;
const ull HALF = QUAR * 2;
const ull THRQ = QUAR * 3;

const int MAXO = 4;
struct Model {
    map<int, int> f;
    int c;
    Model() {c=f[256]=1;}
    int u(int t) {
        if (c < MAXC)
            ++c, ++f[t];
    }
};
map<ull, Model> f[MAXO + 1];
set<int> ex_mask;
int get_ord() {
    ex_mask.clear();
    ull k = 0;
    if (cur == -1) return -1;
    int ord = 1;
    for (; cur - ord + 1 >= 0 && ord <= MAXO; ++ord) {
        k = k << 8 | buf[cur - ord + 1];
        if (f[ord].count(k) == 0)
            break;
    }
    return ord - 1;
}

bool get_char(int &c, ull r, ull l, int&ord, ull&tot, ull&o, ull&h) {
    ull k = 0, v;
    for (int i = 0; i < ord; ++i)
        k = k << 8 | buf[cur - i];
    if (ord == -1) {
        tot = 257;
        v = (l * tot - 1) / r;
        c = o = v;
        h = o + 1;
        return false;
    }
    tot = 0;
    Model*m = &f[ord][k];
    for (int i = 0; i < 257; ++i)
        if (ex_mask.find(i) == ex_mask.end())
            tot += m->f[i];
    v = (l * tot - 1) / r;

    tot = 0;
    c = -1;
    for (int i = 0; i < 256; ++i)
        if (ex_mask.find(i) == ex_mask.end()) {
            int t = m->f[i];
            tot += t;
            if (t != 0) ex_mask.insert(i);
            if (tot > v && c == -1) {
                o = tot - t;
                h = tot;
                c = i;
                v = MAXC;
            }
        }
    if (c == -1) {
        c = 256;
        o = tot;
        h = tot = tot + m->f[256];
        --ord;
        return true;
    }
    tot += m->f[256];
    return false;
}

void update(int c, int ord) {
    ull k = 0;
    for (int i = 0; i < ord; ++i) {
        k = k << 8 | buf[cur - i];
    }
    for (int i = max(ord, 0); i <= MAXO; ++i) {
        if (!f[i].count(k))f[i][k]=Model();
        f[i][k].u(c);
        if (cur - i >= 0)
            k = k << 8 | buf[cur - i];
        else break;
    }
}

unsigned char ibuf[N];
int ibuf_size, icur, mask;
bool next_bit() {
    bool ret = mask & ibuf[icur];
    mask >>= 1;
    if (mask == 0) {
        mask = 0x80;
        if (icur < ibuf_size)
            ++icur;
        else ibuf[icur] = 0;
    }
    return ret;
}
int main() {
    ibuf_size = fread(ibuf, 1, N, fopen("c", "rb"));
    icur = 0;
    mask = 0x80;

    cur = -1;
    f[0][0]=Model();

    ull h = MAXC;
    ull o = 0;
    ull value = 0, _tot, _o, _h;
    int ord, c;
    bool escape;
    for (int i = 0; i < 16; ++i)
        value = value << 1 | next_bit();
    for (;;) {
        ord = get_ord();
        do {
            ull range = h - o + 1;
            escape = get_char(c, range, value - o + 1, ord, _tot, _o, _h);
            h = o + (range * _h) / _tot - 1;
            o = o + (range * _o) / _tot;
            for(;;) {
                if (h < HALF) {
                } else if (o >= HALF) {
                    value -= HALF;
                    o -= HALF;
                    h -= HALF;
                } else if (o >= QUAR && h < THRQ) {
                    value -= QUAR;
                    o -= QUAR;
                    h -= QUAR;
                } else break;
                o <<= 1;
                h <<= 1;
                h++;
                value <<= 1;
                value += next_bit() ? 1 : 0;
            }
            if (c != 256) {
                update(c, ord);
                buf[++cur] = c;
                cout << bitset<8>(c);
            }
        } while (escape);
        if (c == 256) break;
    }

    return 0;
}