#include <bits/stdc++.h>
using namespace std;
const int N=1e6;
unsigned char b[N],B[N];
typedef unsigned long long ull;
ull C=(1<<24)-1,Q=1<<22,H=Q*2,T=Q*3,k,v;
int S,I,A,R,e[257];
struct Model{
    map<int,int> f;int c;
    Model(){c=f[256]=1;}
    int u(int t){++c,++f[t];}
};
map<ull,Model> f[5];
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
            tot += m->f[i]*!e[i];
    v=(l * tot - 1) / r;

    tot=0;
    c=-1;
    for (int i=0;i < 256;++i)
        if(!e[i]) {
            int t=m->f[i];
            tot += t;
            if(t != 0) e[i]=1;
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
        h=tot=tot+1;
        --d;k>>=8;
        return true;
    } ++tot;
    return false;
}
main() {
    S=fread(B,1,N,fopen("c","rb"));
    A=0x80;

    R=-1;
    f[0][0]=Model();

    ull h=C;
    ull o=0;
    ull V=0,_tot,_o,_h;
    int d,c;
    bool escape;
    V = B[0] << 16 | B[1] << 8 | B[2];
    I = 3;
    for (;;) {
        memset(e,0,257*4);
        k=0;
        if(!~R)d=-1;else for (d=0;R - d >= 0 && d<4;++d) {
            k=k << 8 | b[R - d];
            if(f[d+1].count(k) == 0) {
                k >>= 8;
                break;
            }
        }
        do {
            ull range=h - o + 1;
            escape=get_char(c,range,V - o + 1,d,_tot,_o,_h);
            h=o + (range * _h) / _tot - 1;
            o=o + (range * _o) / _tot;
            V:
                if(o>=H)
                    V-=H,o-=H,h-=H; 
                    else if(o>=Q&&h<T)V-=Q,o-=Q,h-=Q;
                else if(h>=H)goto E;
                o*=2;h=h*2+1;
                V=V*2+(bool)(A&B[I]);
                A/=2;A=!A?I+=I<S?1:B[I]=0,0x80:A;
            goto V;E:;
        } while(escape);
        if(c == 256) break;
        for (int i=max(d,0);i<=4;++i) {
            if(!f[i].count(k))f[i][k]=Model();
            f[i][k].u(c);
            if(R-i+1)
                k=k<<8|b[R-i];
            else break;
        }
        b[++R]=c;
        cout<<bitset<8>(c);
    }
}
