#include <bits/stdc++.h>
using namespace std;
const int N=1e6;
unsigned char b[N],B[N];
typedef long long U;
U C=(1<<24)-1,Q=1<<22,H=Q*2,T=Q*3,k,v,h=C,o,V,Z,X,Y,W=256;
int S,I,A,R,e[257],i,d,c,E;
struct D{
    map<int,int> f;int c;
    D(){c=f[W]=1;}
    int u(int t){++c,++f[t];}
};
map<U,D> f[5];
main(){
    S=fread(B,1,N,fopen("c","rb"));A=128;R=-1;
    f[0][0]=D();
    V = *B << 16 | B[1] *W | B[2];
    I = 3;
    for (;;) {
        fill(e,e+257,0);
        k=0;
        if(!~R)d=-1;else for(d=0;R-d+1&&d<4;++d) {
            k=k*W | b[R - d];
            if(!f[d+1].count(k)) {
                k >>= 8;
                break;
            }
        }
        do {
            U r=h - o + 1,l=V - o + 1;
            E=0;
            if(!~d) {
                Z=257;
                c=X=v=(l * Z - 1) / r;
                Y=X + 1;
            } else {
                Z=0;
                D*m=&f[d][k];
                for (i=257;~--i;)Z += m->f[i]*!e[i];
                v=(l * Z - 1) / r;

                Z=0;
                c=W;
                for (i=0;i<W;++i)
                    if(!e[i]) {
                        int t=m->f[i];
                        e[i]=!!t;
                        v<(Z+=t) ? 
                            X=Z - t,
                            Y=Z,
                            c=i,
                            v=C:0;
                    }
                ++Z;
                c>>8?X=Z-1,Y=Z,--d,k>>=8,E=1:0;
            }
            h=o + r * Y / Z - 1;
            o+=r * X / Z;
            for(;;){
                if(o>=H)
                    V-=H,o-=H,h-=H; 
                    else if(o>=Q&&h<T)V-=Q,o-=Q,h-=Q;
                else if(h>=H)break;
                o*=2;h=h*2+1;
                V=V*2+!!(A&B[I]);
                A/=2;A=!A?I+=I<S?1:B[I]=0,128:A;
            }
        } while(E);
        if(c>>8) break;
        for (i=d+!~d;i<5;++i) {
            if(!f[i].count(k))f[i][k]=D();
            f[i][k].u(c);
            if(R-i+1)
                k=k*W|b[R-i];
            else break;
        }
        b[++R]=c;
        cout<<bitset<8>(c);
    }
}
