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
int freq[258], freq_count;
void get_prob(int c, ull&tot, ull&low, ull&high) {
    tot = freq[257];
    low = freq[c];
    high = freq[c + 1];
}
void update(int c) {
    if (freq[257] < MAXT) {
        for (int i = c + 1; i < 258; ++i)
            ++freq[i];
    }
}
void get_char(ull sval, int &c, ull&tot, ull&low, ull&high) {
    for (int i = 0; i < 257; ++i) {
        if (sval < freq[i + 1]) {
            c = i;
            tot = freq[257];
            low = freq[i];
            high = freq[i + 1];
            update(c);
            return ;
        }
    }
    assert(false);
}

const int N = 1e6;
char buf[N];
int buf_size, cur, mask;
void read_init() {
    buf_size = fread(buf, 1, N, fopen("c", "rb"));
    cur = 0;
    mask = 0x80;
}
bool next_bit() {
    bool ret = mask & buf[cur];
    mask >>= 1;
    if (mask == 0) {
        mask = 0x80;
        if (cur < buf_size)
            ++cur;
        else buf[cur] = 0;
    }
    return ret;
}

void decompress() {
    for (int i = 0; i < 258; ++i)
        freq[i] = i;

    ull high = MAXC;
    ull low = 0;
    ull value = 0, _tot, _low, _high;
    for (int i = 0; i < CODE_VALUE_BITS; ++i)
        value = value << 1 | next_bit();
    for (;;) {
        ull range = high - low + 1;
        ull sval = ((value - low + 1) * freq[257] - 1) / range;
        int c;
        get_char(sval, c, _tot, _low, _high);
        //cout << high << ' ' << low << ' ' << sval << ' ' << c << endl;
        if (c == 256) break;
        cout << bitset<8>(c);
        //cout << endl;;
        //return ;
        high = low + (range * _high) / _tot - 1;
        low = low + (range * _low) / _tot;
        for(;;) {
            if (high < HALF) {
            //do nothing, bit is a zero
            } else if (low >= HALF) {
                value -= HALF;  //subtract one half from all three code values
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
    }
}

int main() {

    read_init();
    decompress();

    return 0;
}