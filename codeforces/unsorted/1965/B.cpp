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

	int tc = 1;
	cin >> tc;
	while (tc--)
	{
		go();
	}
}

void go()
{
	int n, k;
	cin >> n >> k;

	n++;
	int p2 = 1;
	while (2 * p2 <= k)
		p2 *= 2;
	
	vector<int> ans{k - p2, k + 1, 2 * k + 1};
	for (int x = 1; x < p2; x *= 2)
		ans.push_back(x);
	for (int x = k * 2; x < n; x *= 2)
		ans.push_back(x);
	
	cout << size(ans) << '\n';
	for (int a : ans)
		cout << a << ' ';
	cout << '\n';
}
