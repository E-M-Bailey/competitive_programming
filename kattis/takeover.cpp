#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
	int n, m, tc = 0;
	while (cin >> n >> m) {
		cout << "Case " << ++tc << ": ";
		string NA = "Takeover Incorporated", NB = "Buyout Limited";
		map<int64_t, int> A, B;
		for (int i = 0; i < n; i++) {
			int64_t a;
			cin >> a;
			A[a]++;
		}
		for (int i = 0; i < m; i++) {
			int64_t b;
			cin >> b;
			B[b]++;
		}
		while (true) {/*
		    cerr << "A:" << endl;
            for (auto [a, c] : A)
                cerr << ' ' << a << " x " << c << endl;
            cerr << "B:" << endl;
            for (auto [b, c] : B)
                cerr << ' ' << b << " x " << c << endl;*/
            if (A.empty()) {
                cout << NB << endl;
                break;
            }
			auto ita = prev(A.end()), itb = prev(B.end());
			int64_t maxa = ita->first;
			int64_t maxas2 = maxa;
			auto ita2 = n == 1 ? A.end() : ita->second > 1 ? ita : prev(ita);
			if (n > 1) maxas2 += ita2->first;
			if (maxas2 < itb->first) {
				cout << NB << endl;
				break;
			} else if (maxa < itb->first) {
                if (!--ita->second)
                    A.erase(ita);
                if (!--ita2->second)
                    A.erase(ita2);
                A[maxas2]++;
                n--;
			}
			else {
                if (!--itb->second)
                    B.erase(itb);
                m--;
			}
			swap(A, B);
			swap(n, m);
			swap(NA, NB);
		}
	}
}
