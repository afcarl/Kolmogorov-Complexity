#include<cstdio>
int i,j;main(){for(;i<4096;++i)for(j=0;j<12;)putchar("0110"[i>>j++&3]);}