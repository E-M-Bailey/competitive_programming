#include <bits/stdc++.h>
using namespace std;
typedef unsigned __int128 u128;
constexpr u128 ONE = 1;
int main(int argc, char* argv[]) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
	int n, tc = 0;
    const auto dbg = [&](ostream& strm, u128 x) -> ostream& {
        u128 m = 1;
        for (int i = 0; i < n; i++, m *= 2)
            strm << ((x & m) == m);
        return strm;
    };
	while (cin >> n) {
		vector<u128> M(n, 0);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				char c;
				cin >> c;
				if (c == '1')
                    M[i] |= ONE << j;
			}
			M[i] |= ONE << i;
		}
		//for (u128 m : M)
        //    dbg(cerr, m) << endl;
        //cerr << endl;
		u128 mm = (ONE << n) - 1;
		vector<int> ans(6, -1);
		for (int i0 = 0; ans.size() > 1 && i0 < n; i0++) {
			u128 m0 = M[i0];
            //if (i0 == 1)
            //    dbg(dbg(cerr << ' ', m0) << ' ', mm) << endl;
                //cerr << (m0 ^ mm) << endl;
			if (m0 == mm) {
				ans = {i0};
				break;
			}
			for (int i1 = 0; ans.size() > 2 && i1 < i0; i1++) {
				u128 m1 = M[i1] | m0;
				if (m1 == mm) {
					ans = {i0, i1};
					break;
				}
				for (int i2 = 0; ans.size() > 3 && i2 < i1; i2++) {
					u128 m2 = M[i2] | m1;
					if (m2 == mm) {
						ans = {i0, i1, i2};
						break;
					}
					for (int i3 = 0; ans.size() > 4 && i3 < i2; i3++) {
						u128 m3 = M[i3] | m2;
						if (m3 == mm) {
							ans = {i0, i1, i2, i3};
							break;
						}
						for (int i4 = 0; ans.size() > 5 && i4 < i3; i4++) {
							u128 m4 = M[i4] | m3;
							if (m4 == mm) {
								ans = {i0, i1, i2, i3, i4};
								break;
							}
						}
					}
				}
			}
		}

		if (ans[0] < 0) {
			u128 V = mm;
			while (V) {
				int bi = -1, bc = -1;
				for (int i = 0; i < n; i++)
					if (V & (ONE << i)) {
						u128 m = M[i] & V;
						uint64_t hi = m >> 64, lo = m;
						int c = __builtin_popcount(hi) + __builtin_popcount(lo);
						if (c > bc) {
							bi = i;
							bc = c;
						}
					}
				V &= ~M[bi];
				ans.push_back(bi);
			}
		}
		cout << "Case " << ++tc << ": " << ans.size();
		for (int a : ans)
            cout << ' ' << a + 1;
        cout << endl;
	}
}
