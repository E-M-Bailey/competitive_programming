#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;
array<array<i64, 801>, 801> G{}, G2;
int main() {
	//cerr << "hi?" << endl;
	int n;
	cin >> n;
	G[400][400] = 1;
	//i64& O = G[400][400];
	//O = 1;
	//cerr << "yo" << endl;
	for (int i = 0; i < n; i++) {
		G2 = G;
		int x, y;
		cin >> x >> y;
		int alo = max(0, -x), bhi = min(0, -x) + 801;
		int blo = max(0, -y), ahi = min(0, -y) + 801;
		for (int a = alo; a < ahi; a++)
			for (int b = blo; b < bhi; b++) {
				int c = a + x, d = b + y;
				//cerr << a << ' ' << b << ' ' << c << ' ' << d << endl;
				G[c][d] += G2[a][b];
			}
	}
	cout << G[400][400] - 1;
}
