#include <bits/stdc++.h>
using namespace std;
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


const int N = 1e6;
char buf[N];
int buf_size, cur;
void read_init() {
    buf_size = fread(buf, 1, N, fopen("i.b", "rb"));
    cur = 0;
}
int next_byte() {
    if (cur < buf_size)
        return (int)buf[cur++];
    return -1;
}


ofstream out("c", ios::binary);
char oc;
int cnt;
int byte_count = 0;
void put_bit(int b) {
    oc = oc << 1 | b;
    ++cnt;
    if (cnt == 8) {
        out.write(&oc, 1);
        oc = 0;
        cnt = 0;
        ++byte_count;
        assert(byte_count < 1000000);
    }
}
void close_output() {
    if (cnt > 0) {
        oc = oc << (8 - cnt);
        out.write(&oc, 1);
        cnt = 0;
    }
}
void put(int b, int&pending_bits) {
    put_bit(b);
    while (pending_bits--) {
        put_bit(!b);
    }
    pending_bits = 0;
}

void compress() {
    for (int i = 0; i < 258; ++i)
        freq[i] = i;

    int pending_bits = 0;
    ull low = 0;
    ull high = MAXC;
    ull _tot, _low, _high;
    for (;;) {
        int c = next_byte();
        if (c == -1)
            c = 256;
        get_prob(c, _tot, _low, _high);
        update(c);
        ull range = high - low + 1;
        high = low + range * _high / _tot - 1;
        low = low + range * _low / _tot;
        for (;;) {
            // cout << low << ' ' << high << endl;
            if (high < HALF) {
                put(0, pending_bits);
            } else if (low >= HALF) {
                put(1, pending_bits);
            } else if (low >= QUAR && high < THRQ) {
                ++pending_bits;
                low -= QUAR;
                high -= QUAR;
            } else break;
            high <<= 1;
            high |= 1;
            low <<= 1;
            high &= MAXC;
            low &= MAXC;
        }
        if (c == 256) break;
    }
    ++pending_bits;
    if (low < QUAR)
        put(0, pending_bits);
    else
        put(1, pending_bits);
}

int main() {
    read_init();
    compress();
    close_output();
    return 0;
}