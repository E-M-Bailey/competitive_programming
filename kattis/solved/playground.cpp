#include <bits/stdc++.h>

using namespace std;

int64_t in()
{
	string s;
	cin >> s;
	auto k = s.find('.');
	if (k == string::npos)
	{
		k = size(s);
		s += '.';
	}
	s.resize(k + 4, '0');
	return stoi(s.substr(0, k)) * (int64_t)1000 + stoi(s.substr(k + 1));
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	int k;
	while (cin >> k, k)
	{
		vector<int64_t> A(k);
		for (auto &a : A)
			a = in();
		sort(begin(A), end(A));
		int64_t sum	 = 0;
		bool	good = false;
		for (int i = 1; i < k; i++)
		{
			sum += A[i - 1];
			good |= A[i] <= sum;
		}
		cout << (good ? "YES\n" : "NO\n");
	}
}
