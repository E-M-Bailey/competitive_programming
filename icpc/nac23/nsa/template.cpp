#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC optimize("avx2,bmi,bmi2,lzcnt,popcnt")

#define rep(i,a,b) for (int i = a; i<(b); ++i)
#define all(x) begin(x),end(x)
#define sz(x) int(size(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
	#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
}

// g++ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out