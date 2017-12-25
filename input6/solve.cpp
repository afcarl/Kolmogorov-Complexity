#include<cstdio>
int i;main(){for(;i<49152;)putchar("0110"[i/12>>i++%12&3]);}