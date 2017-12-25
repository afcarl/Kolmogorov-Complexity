#include<cstdio>
main(){for(int i;i<49152;)printf("0110"[i/12>>i++%12&3]);}