#include<bits/stdc++.h>
int D[28],*c,d;char s[51],*i=s;int main(){std::cin>>s;for(std::iota(D,D+27,0);*i;)for(c=D+*i++-97,d=*c;d<*++c;)*c=d++;std::cout<<D[26];}