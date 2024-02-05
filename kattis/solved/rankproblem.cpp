#include <bits/stdc++.h>

using namespace std;

int main()
{
	int n, m;
	cin >> n >> m;
	vector<string> A(n);
	for (int i = 0; i < n; i++)
		A[i] = "T" + to_string(i + 1);
	while (m--)
	{
		string a, b;
		cin >> a >> b;
		auto at = find(begin(A), end(A), a), bt = find(begin(A), end(A), b);
		if (at > bt)
			rotate(bt, bt + 1, at + 1);
	}
	for (string a : A)
		cout << a << ' ';
}
