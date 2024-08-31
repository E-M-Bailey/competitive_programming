#include <bits/stdc++.h>

using namespace std;

#define ALL(C) begin(C), end(C)

void go();

int main(int argc, char const *argv[])
{
	cin.tie(0)->sync_with_stdio(0);
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int t;
	cin >> t;
	while (t--)
		go();
}

void go()
{
	int n;
	cin >> n;
	vector<int> F(n);
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		F[a]++;
	}
	
	int ans = 0;
	bool one = true;
	while (ans < n && F[ans] > 0 && (one || F[ans] > 1))
	{
		one &= F[ans] > 1;
		ans++;
	}
	cout << ans << '\n';
}
