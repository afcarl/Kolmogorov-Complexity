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
set<int> ex_m;
int get_d() {
    ex_m.clear();
    ull k = 0;
    if (cur == -1) return -1;
    int d = 1;
    for (; cur - d + 1 >= 0 && d <= MAXO; ++d) {
        k = k << 8 | buf[cur - d + 1];
        if (f[d].count(k) == 0)
            break;
    }
    return d - 1;
}

bool get_char(int &c, ull r, ull l, int&d, ull&tot, ull&o, ull&h) {
    ull k = 0, v;
    for (int i = 0; i < d; ++i)
        k = k << 8 | buf[cur - i];
    if (d == -1) {
        tot = 257;
        v = (l * tot - 1) / r;
        c = o = v;
        h = o + 1;
        return false;
    }
    tot = 0;
    Model*m = &f[d][k];
    for (int i = 0; i < 257; ++i)
        if (ex_m.find(i) == ex_m.end())
            tot += m->f[i];
    v = (l * tot - 1) / r;

    tot = 0;
    c = -1;
    for (int i = 0; i < 256; ++i)
        if (ex_m.find(i) == ex_m.end()) {
            int t = m->f[i];
            tot += t;
            if (t != 0) ex_m.insert(i);
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
        --d;
        return true;
    }
    tot += m->f[256];
    return false;
}

void update(int c, int d) {
    ull k = 0;
    for (int i = 0; i < d; ++i) {
        k = k << 8 | buf[cur - i];
    }
    for (int i = max(d, 0); i <= MAXO; ++i) {
        if (!f[i].count(k))f[i][k]=Model();
        f[i][k].u(c);
        if (cur - i >= 0)
            k = k << 8 | buf[cur - i];
        else break;
    }
}

unsigned char ibuf[N];
int ibuf_size, icur, m;
bool next_bit() {
    bool ret = m & ibuf[icur];
    m >>= 1;
    if (m == 0) {
        m = 0x80;
        icur += icur<ibuf_size?1:ibuf[icur]=0;
    }
    return ret;
}
int main() {
    ibuf_size = fread(ibuf, 1, N, fopen("c", "rb"));
    m = 0x80;

    cur = -1;
    f[0][0]=Model();

    ull h = MAXC;
    ull o = 0;
    ull value = 0, _tot, _o, _h;
    int d, c;
    bool escape;
    for (int i = 0; i < 16; ++i)
        value = value << 1 | next_bit();
    for (;;) {
        d = get_d();
        do {
            ull range = h - o + 1;
            escape = get_char(c, range, value - o + 1, d, _tot, _o, _h);
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
                update(c, d);
                buf[++cur] = c;
                cout << bitset<8>(c);
            }
        } while (escape);
        if (c == 256) break;
    }

    return 0;
}