#include <bits/stdc++.h>

using namespace std;

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int HP[10'001]{};
	for (int i = 2; i <= 10'000; i++)
	{
		if (HP[i])
			continue;
		for (int j = i; j <= 10'000; j += i)
			HP[j] = i;
	}
	
	int ans[10'001];
	ans[2] = 5;
	for (int N = 3; N <= 10'000; N++)
	{
		int phi = N;
		for (int n = N; n > 1;)
		{
			int hp = HP[n];
			phi = phi / hp * (hp - 1);
			do
				n /= hp;
			while (HP[n] == hp);
		}
		ans[N] = ans[N - 1] + 3 * phi;
	}

	int T;
	cin >> T;
	while (T--)
	{
		int K, N;
		cin >> K >> N;
		cout << K << ' ' << ans[N] << "/2\n";
	}
}