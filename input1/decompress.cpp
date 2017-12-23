#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
char buf[N];
int buf_size, cur;

typedef unsigned long long ull;
const ull CODE_VALUE_BITS  = 16;
const ull FREQUENCY_BITS = 14;
const ull MAXC = (1ull << CODE_VALUE_BITS) - 1;
const ull MAXT = (1ull << FREQUENCY_BITS) - 1;
const ull QUAR = (1ull << CODE_VALUE_BITS - 2);
const ull HALF = QUAR * 2;
const ull THRQ = QUAR * 3;

const int MAXO = 4;
struct Model {
    map<int, int> f;
    int c;
    Model() {
        c = 0;
    }
};
map<ull, Model> freq[MAXO + 1];
void model_init() {
    cur = -1;
    freq[0][0ull] = Model();
    freq[0][0ull].f[256] = 1; // for escape
    freq[0][0ull].c = 1;
}
set<int> ex_mask;
int get_ord() {
    ex_mask.clear();
    ull key = 0;
    if (cur == -1) return -1;
    int ord = 1;
    for (; cur - ord + 1 >= 0 && ord <= MAXO; ++ord) {
        key = key << 8 | buf[cur - ord + 1];
        if (freq[ord].count(key) == 0)
            break;
    }
    return ord - 1;
}

bool get_char(int &c, ull r, ull l, int&ord, ull&tot, ull&low, ull&high) {
    ull key = 0, v;
    for (int i = 0; i < ord; ++i)
        key = key << 8 | buf[cur - i];
    if (ord == -1) {
        tot = 257;
        v = (l * tot - 1) / r;
        c = low = v;
        //if (c == 256) exit(0);
        high = low + 1;
        return false;
    }
    tot = 0;
    for (int i = 0; i < 257; ++i)
        if (ex_mask.find(i) == ex_mask.end())
            tot += freq[ord][key].f[i];
    v = (l * tot - 1) / r;

    tot = 0;
    c = -1;
    for (int i = 0; i < 256; ++i)
        if (ex_mask.find(i) == ex_mask.end()) {
            int t = freq[ord][key].f[i];
            tot += t;
            if (t != 0) ex_mask.insert(i);
            if (tot > v && c == -1) {
                low = tot - t;
                high = tot;
                c = i;
                v = MAXT;
            }
        }
    if (c == -1) {
        c = 256;
        low = tot;
        high = tot = tot + freq[ord][key].f[256];
        --ord;
        return true;
    }
    tot += freq[ord][key].f[256];
    return false;
}

void update(int c, int ord) {
    // printf("%d %d\n", c, ord);
    //if (ord == -1) return;
    ull key = 0;
    for (int i = 0; i < ord; ++i) {
        key = key << 8 | buf[cur - i];
    }
    for (int i = max(ord, 0); i <= MAXO; ++i) {
        if (freq[i].count(key) == 0) {
            freq[i].insert(make_pair(key, Model()));
            freq[i][key].c = 2;
            freq[i][key].f[c] = 1;
            freq[i][key].f[256] = 1;
        } else {
            if (freq[i][key].c >= MAXT) {
                freq[i][key].c = 0;
                for (int j = 0; j < 256; ++j) {
                    freq[i][key].f[j] /= 2;
                    freq[i][key].c += freq[i][key].f[j];
                }
                freq[i][key].c += freq[i][key].f[256];
            }
            ++freq[i][key].c;
            ++freq[i][key].f[c];
            ///printf("%d %ull\n", i, key);
        }
        if (cur - i >= 0)
            key = key << 8 | buf[cur - i];
        else break;
    }
}

char ibuf[N];
int ibuf_size, icur, mask;
void read_init() {
    ibuf_size = fread(ibuf, 1, N, fopen("c", "rb"));
    icur = 0;
    mask = 0x80;
}
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

void decompress() {
    model_init();

    ull high = MAXC;
    ull low = 0;
    ull value = 0, _tot, _low, _high;
    int ord, c;
    bool escape;
    for (int i = 0; i < CODE_VALUE_BITS; ++i)
        value = value << 1 | next_bit();
    for (;;) {
        ord = get_ord();
        do {
            ull range = high - low + 1;
            //ull sval = ((value - low + 1) * freq[257] - 1) / range;
            escape = get_char(c, range, value - low + 1, ord, _tot, _low, _high);
            //cout << c << endl;
            high = low + (range * _high) / _tot - 1;
            low = low + (range * _low) / _tot;
            for(;;) {
                if (high < HALF) {
                } else if (low >= HALF) {
                    value -= HALF;
                    low -= HALF;
                    high -= HALF;
                } else if (low >= QUAR && high < THRQ) {
                    value -= QUAR;
                    low -= QUAR;
                    high -= QUAR;
                } else break;
                low <<= 1;
                high <<= 1;
                high++;
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
}

int main() {

    read_init();
    decompress();

    return 0;
}