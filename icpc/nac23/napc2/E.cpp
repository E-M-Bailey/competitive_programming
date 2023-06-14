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
typedef long double ld;

const int LIM = 1e7 + 1;

ll sq(ld R){
	ll res = 0;
	for(int i = 1; i < R; i++){
		int x = (int) (sqrt(R*R-i*i)+1e-10);
		res += 4*x;
	}
	return res;
}

int main()
{
#ifdef DBG
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
#endif
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	ll S;
	cin >> S;
	ld b = 1.0, e = 50000.0;
	//cout << sq(e) << endl;

	while(e-b > 1e-9){
		ld m = (e+b)/2;
		if(sq(m) <= S) b = m;
		else e = m;
	}
	ld res = e;

	cout << fixed << setprecision(9) << res << endl;
}

// g+ -g -O2 -std=gnu++20 -static -DDBG X.cpp && ./a.out