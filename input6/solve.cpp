#include<cstdio>
int i,j;main(){for(;j<12||(j=0,++i<4096);)putchar("0110"[i>>j++&3]);}