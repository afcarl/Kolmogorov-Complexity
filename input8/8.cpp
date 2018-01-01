#include<bits/stdc++.h>
int x[11];int t(int c,int l,int r,int i){if(i>9)for(i=0;i<11;++i)std::cout<<std::bitset<10>(x[i]);else for(int p=1023&~(c|l|r),q;q=p&-p,p;p-=q)x[i]=1<<(9-(int)log2(q)),t(c|q,(l|q)*2,(r|q)/2,i+1);}main(){x[10]=1023;t(0,0,0,0);}
