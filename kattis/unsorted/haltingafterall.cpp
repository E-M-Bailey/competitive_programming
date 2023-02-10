#include <bits/stdc++.h>
using namespace std;

struct TM {
	int n;
	vector<array<int, 2>> T;
	vector<array<bool, 2>> O;
	vector<array<bool, 2>> D;
	TM(int n) :
		n(n),
		T(n),
		O(n),
		D(n) {
		int s, i, t, o, d;
		for (int j = 0; j < 2 * n; j++) {
			cin >> s >> i >> t >> o >> d;
			T[s][i] = t;
			O[s][i] = o;
			D[s][i] = d;
		}
	}
	bool halt(int tape, int steps) {
		int s = 0, mask = 1;
		for (int j = 0; j < steps; j++) {
			bool i = tape & mask;
			if (O[s][i])
				tape |= mask;
			else
				tape &= ~mask;
			if (D[s][i])
				mask <<= 1;
			else if (mask != 1)
				mask >>= 1;
			s = T[s][i];
			if (s < 0)
				return true;
		}
		return false;
	}
};

int main(int argc, char* argv[]) {
    if (argc > 1) {
        freopen(argv[1], "r", stdin);
        freopen(argv[2], "w", stdout);
    }
	int l, s;
	cin >> l >> s;
	TM tm(s);
	for (int tape = 0; tape < (1 << l); tape++)
		if (!tm.halt(tape, l)) {
            cout << 0;
            return 0;
		}
    cout << 1;
}
