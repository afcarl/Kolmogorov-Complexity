#include<cstdio>
int i;main(){for(;i<49152;)putchar("0110"[i/6>>i++%12+1&3]);}