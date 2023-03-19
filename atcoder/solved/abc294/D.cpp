#include <bits/stdc++.h>
using namespace std;
int main()
{
	int n, q;
	cin >> n >> q;
	vector<int> A(n);
	iota(begin(A), end(A), 1);
	reverse(begin(A), end(A));
	set<int> C;
	while (q--)
	{
		int c, x;
		cin >> c;
		switch (c) {
			case 1:
				C.insert(A.back());
				A.pop_back();
				break;
			case 2:
				cin >> x;
				C.erase(x);
				break;
			case 3:
				cout << *C.begin() << endl;
				break;
		}
	}
}