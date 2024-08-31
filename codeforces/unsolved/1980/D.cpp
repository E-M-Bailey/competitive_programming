#include <bits/stdc++.h>

using namespace std;

#define sz(C)  (int(size(C)))
#define all(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	cin.tie(0)->sync_with_stdio(0);

	int tc = 1;
	cin >> tc;
	while (tc--)
		go();
}

void go()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;

	int pos = -1;
	for (int i = 0; i < n - 2; i++)
	{
		int a = gcd(A[i], A[i + 1]), b = gcd(A[i + 1], A[i + 2]);
		if (a > b)
		{
			pos = i;
			break;
		}
	}
	if (pos < 0)
	{
		cout << "YES\n";
		return;
	}

	for (int p = pos; p < pos + 3; p++)
	{
		vector<int> B = A;
		B.erase(begin(B) + p);
		bool good = true;
		for (int i = 0; i < n - 3; i++)
		{
			int a = gcd(B[i], B[i + 1]), b = gcd(B[i + 1], B[i + 2]);
			good &= a <= b;
		}
		if (good)
		{
			cout << "YES\n";
			return;
		}
	}
	cout << "NO\n";
}
