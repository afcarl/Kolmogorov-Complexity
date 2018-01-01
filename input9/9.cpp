#include<bits/stdc++.h>
main(){for(unsigned a=16807,c=1<<31,x=1508303647,y,i=10000;i--;y=a*x,std::cout<<std::bitset<32>(x=(y+y/c%2)%c));}