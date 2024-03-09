#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc > 2)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int n;
	cin >> n;
	vector<int> A(n), T(n), P(n);
	for (int &a : A)
		cin >> a;
	for (int &t : T)
		cin >> t;
	for (int &p : P)
	{
		cin >> p;
		p--;
	}
	auto sum = accumulate(begin(A), end(A), 0ll);
	long double win = 1;
	for (int i = 0; i < n; i++)
	{
		if (A[P[i]] * 2 >= sum)
		{
			win /= 2;
			sum -= A[P[i]];
		}
		else
		{
			rotate(begin(P) + i, begin(P) + i + 1, end(P));
			break;
		}
	}
	cout << fixed << setprecision(6) << win << '\n';
	for (int p : P)
		cout << p + 1 << ' ';
}