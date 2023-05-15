#include <bits/stdc++.h>

using namespace std;

const int N = 10'001;
bool C[N]{};
int H[N];
int DS[N]{};
bool onS[N]{};
vector<int> S;

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	for (int i = 2; i < N; i++)
		if (!C[i])
			for (int j = i * 2; j < N; j += i)
				C[j] = true;

	for (int m = 0; m < N; m++)
		for (int x = m; x; x /= 10)
			DS[m] += (x % 10) * (x % 10);

	fill(begin(H), end(H), -1);

	int T;
	cin >> T;
	while (T--)
	{
		int tc, m;
		cin >> tc >> m;

		cout << tc << ' ' << m << ' ';

		if (m <= 1 || C[m])
		{
			cout << "NO\n";
			continue;
		}

		S.push_back(m);
		for (int x = m; H[x] < 0 && !onS[x]; S.push_back(x = DS[x]))
			onS[x] = true;
		int val = H[S.back()];
		if (val < 0)
			val = S.back() == 1;
		for (int x : S)
		{
			H[x] = val;
			onS[x] = false;
		}
		S.clear();
		cout << (H[m] ? "YES\n" : "NO\n");
	}
}