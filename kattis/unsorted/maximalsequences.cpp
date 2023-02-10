#include <bits/stdc++.h>
using namespace std;
typedef unordered_set<int> usi;

/*
struct Tree {
	typedef usi T;
	static const T UNIT;
	T f(T& L, T& R) {
        T ans;
        for (int l : L)
            ans.insert(l);
        for (int r : R)
            ans.insert(r);
        return ans;
	}
	int n, m;
	vector<vector<T>> D;
	Tree(vector<T> leaves) :
		n(leaves.size()),
		D(1, leaves) {
        while (D.back().size() > 1) {
            vector<T> layer(D.back().size() / 2);
            for (int i = 0; i < D.back().size(); i += 2)
                layer[i / 2] = f(D.back()[i], D.back()[i + 1]);
            D.push_back(move(layer));
        }

	}
};
const usi Tree::UNIT{};
*/

bool in(int x, const vector<int>& A) {
	for (int a : A)
		if (a == x)
			return true;
	return false;
}
bool allIn(const usi& X, const vector<int>& A) {
	int ct = 0;
	for (int a : A)
		ct += X.find(a) != X.end();
	return ct == X.size();
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
		freopen(argv[2], "w", stdout);
	}
	int n;
	cin >> n;
	vector<int> A(n);
	for (int& a : A)
		cin >> a;
	int m = 0;
	while (m * m < n)
		m++;
	while (n < m * m) {
		A.push_back(-1);
		n++;
	}
	vector<usi> B(m);
	for (int i = 0; i < n; i++)
		B[i / m].insert(A[i]);
	cerr << m << endl;
	for (const auto& BB : B) {
		for (int b : BB)
			cerr << b << ' ';
		cerr << endl;
	}
	int q;
	cin >> q;
	//cerr << q << endl;
	while (q--) {
		int i, k;
		cin >> i >> k;
		i--;
		int st = i;
		vector<int> S(k);
		for (int& s : S)
			cin >> s;
		bool done = false;
		while (i % m) {
			if (!in(A[i], S)) {
				done = true;
				//cerr << i << ' ' << A[i] << " not in S 1" << endl;
				break;
			}
			i++;
		}
		if (!done)
			while (i < n) {
				if (!allIn(B[i / m], S)) {
					while (i < n && in(A[i], S))
						i++;
					break;
				}
				i += m;
			}
		cout << i - st << endl;
	}
}
