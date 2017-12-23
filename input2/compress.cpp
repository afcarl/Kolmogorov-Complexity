#include <bits/stdc++.h>
using namespace std;

const int N = 1e6;
unsigned char buf[N];
int buf_size, cur;
void read_init() {
    buf_size = fread(buf, 1, N, fopen("i.b", "rb"));
    cur = -1;
}


typedef unsigned long long ull;
const ull CODE_VALUE_BITS  = 16;
const ull FREQUENCY_BITS = 14;
const ull MAXC = (1ull << CODE_VALUE_BITS) - 1;
const ull MAXT = (1ull << FREQUENCY_BITS) - 1;
const ull QUAR = (1ull << CODE_VALUE_BITS - 2);
const ull HALF = QUAR * 2;
const ull THRQ = QUAR * 3;

const int MAXO = 4;
// -1  等频率, 都是1, 0-255. 这都匹配不到, 那必然是EOF到了.
//  0  纯出现频率
//  1  1阶上文
//  2  2阶上文
//  3  3阶上文
//  4  4阶上文
struct Model {
    map<int, int> f;
    int c;
    Model() {
        c = 0;
    }
};
map<ull, Model> freq[MAXO + 1];
void model_init() {
    freq[0][0ull] = Model();
    freq[0][0ull].f[256] = 1; // for escape
    freq[0][0ull].c = 1;
}

/*
PPM上文预测. 首先查找最远为5的上文, 如果命中则取预测概率进行编码, 否则降阶.
如果当前符号在0频率区, 则取escaep跳转到更低阶的上文. 跳转情况下不应该移动
当前编码位置. 如果escape到-2阶, 则结束编码.
*/
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

bool get_prob(int c, int&ord, ull&tot, ull&low, ull&high) {
    ull key = 0;
    for (int i = 0; i < ord; ++i)
        key = key << 8 | buf[cur - i];
    if (ord == -1) {
        tot = 257;
        low = c;
        high = low + 1;
        return false;
    }
    tot = 0;
    for (int i = 0; i < 256; ++i)
        if (ex_mask.find(i) == ex_mask.end()) {
            int t = freq[ord][key].f[i];
            tot += t;
            if (t != 0) ex_mask.insert(i);
            if (c == i) {
                low = tot - t;
                high = tot;
            }
    }
    if (low == high || c == 256) {
        low = tot;
        high = tot + freq[ord][key].f[256];
        tot = high;
        --ord;
        return true;
    }
    tot += freq[ord][key].f[256];
    return false;
}

void update(int c) {
    ull key = 0;
    for (int ord = 0; ord <= MAXO; ++ord) {
        if (freq[ord].count(key) == 0) {
            freq[ord].insert(make_pair(key, Model()));
            freq[ord][key].c = 2;
            freq[ord][key].f[c] = 1;
            freq[ord][key].f[256] = 1;
        } else {
            if (freq[ord][key].c < MAXT) {
                ++freq[ord][key].c;
                ++freq[ord][key].f[c];
            }
        }
        if (cur - ord >= 0)
            key = key << 8 | buf[cur - ord];
        else break;
    }
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
    model_init();

    int pending_bits = 0;
    ull low = 0;
    ull high = MAXC;
    ull _tot, _low, _high;
    int ord;
    bool escape;
    for (;;) {
        ord = get_ord();
        int c = cur + 1 < buf_size ? buf[cur + 1] : 256;
        do {
            escape = get_prob(c, ord, _tot, _low, _high);
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
        } while (escape);
        if (c == 256) break;
        update(c);
        ++cur;
        //printf("%d\n", cur);
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