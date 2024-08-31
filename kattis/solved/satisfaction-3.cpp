#ifndef DEBUG
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops")
#endif
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,popcnt,abm,mmx,avx,avx2,fma,tune=native")

#include <bits/stdc++.h>

using namespace std;



struct node
{
	int idx;
	vector<int> ch;
};



int main()
{
#ifdef DEBUG
	ignore = freopen("in.txt", "r", stdin);
	ignore = freopen("out.txt", "w", stdout);
#endif
}
