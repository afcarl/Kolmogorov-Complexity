#include <bits/stdc++.h>
using namespace std;
const int N=1e6;
int b_s,cur;
unsigned char b[N],ib[N];
int ib_s,icur,m;

typedef unsigned long long ull;
ull C=65535,Q=16384,H=Q*2,T=Q*3,k,v;

const int MAXO=4;
struct Model{
    map<int,int> f;int c;
    Model(){c=f[256]=1;}
    int u(int t){if(c<C)++c,++f[t];}
};
map<ull,Model> f[MAXO + 1];
set<int> e;
bool get_char(int &c,ull r,ull l,int&d,ull&tot,ull&o,ull&h) {    
    if(d == -1) {
        tot=257;
        v=(l * tot - 1) / r;
        c=o=v;
        h=o + 1;
        return false;
    }

    tot=0;
    Model*m=&f[d][k];
    for (int i=0;i < 257;++i)
        if(!e.count(i))
            tot += m->f[i];
    v=(l * tot - 1) / r;

    tot=0;
    c=-1;
    for (int i=0;i < 256;++i)
        if(!e.count(i)) {
            int t=m->f[i];
            tot += t;
            if(t != 0) e.insert(i);
            if(tot > v && c == -1) {
                o=tot - t;
                h=tot;
                c=i;
                v=C;
            }
        }
    if(c == -1) {
        c=256;
        o=tot;
        h=tot=tot + m->f[256];
        --d;
        k >>= 8;
        return true;
    }
    tot += m->f[256];
    return false;
}

bool next_bit() {
    bool ret=m & ib[icur];
    m >>= 1;
    if(m == 0) {
        m=0x80;
        icur += icur<ib_s?1:ib[icur]=0;
    }
    return ret;
}
main() {
    ib_s=fread(ib,1,N,fopen("c","rb"));
    m=0x80;

    cur=-1;
    f[0][0]=Model();

    ull h=C;
    ull o=0;
    ull value=0,_tot,_o,_h;
    int d,c;
    bool escape;
    for (int i=0;i < 16;++i)
        value=value << 1 | next_bit();
    for (;;) {
        e.clear();
        k=0;
        if(!~cur)d=-1;else for (d=0;cur - d >= 0 && d<MAXO;++d) {
            k=k << 8 | b[cur - d];
            if(f[d+1].count(k) == 0) {
                k >>= 8;
                break;
            }
        }
        do {
            ull range=h - o + 1;
            escape=get_char(c,range,value - o + 1,d,_tot,_o,_h);
            h=o + (range * _h) / _tot - 1;
            o=o + (range * _o) / _tot;
            for(;;) {
                if(h < H) {
                } else if(o >= H) {
                    value -= H;
                    o -= H;
                    h -= H;
                } else if(o >= Q && h < T) {
                    value -= Q;
                    o -= Q;
                    h -= Q;
                } else break;
                o <<= 1;
                h <<= 1;
                h++;
                value <<= 1;
                value += next_bit() ? 1 : 0;
            }
            if(c != 256) {
                for (int i=max(d,0);i<=MAXO;++i) {
                    if(!f[i].count(k))f[i][k]=Model();
                    f[i][k].u(c);
                    if(cur - i >= 0)
                        k=k << 8 | b[cur - i];
                    else break;
                }
                b[++cur]=c;
                cout << bitset<8>(c);
            }
        } while(escape);
        if(c == 256) break;
    }
}
