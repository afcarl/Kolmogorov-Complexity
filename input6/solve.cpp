#include<cstdio>
main(int i){for(--i;i<49152;)putchar("0110"[i/12>>i++%12&3]);}