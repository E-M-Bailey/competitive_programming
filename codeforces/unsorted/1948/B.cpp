#include <bits/stdc++.h>

using namespace std;

void go();

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	cin.tie(0)->sync_with_stdio(0);
	int t = 1;
	cin >> t;
	while (t--)
	{
		go();
	}
}

void go()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int &a : A)
		cin >> a;

	vector<int> B;
	int			mx = 0;
	for (int a : A)
	{
		int x = a / 10, y = a % 10;
		if (x > 0 && mx <= x && x <= y)
		{
			B.push_back(x);
			B.push_back(y);
			mx = y;
		}
		else
		{
			B.push_back(a);
			mx = a;
		}
	}

	cout << (is_sorted(begin(B), end(B)) ? "YES\n" : "NO\n");
}
