#include <bits/stdc++.h>

using namespace std;

int main()
{
	vector<int> I, J;

	int d, s;
	cin >> d >> s;
	vector<pair<int, int>> D(d);
	for (auto &[i, j] : D)
	{
		cin >> j >> i;
		i = -i;
		I.push_back(i);
		J.push_back(j);
	}
	vector<tuple<int, int, int>> S(s);
	for (auto &[i, j1, j2] : S)
	{

	}
	sort(begin(D), end(D), [](pair<int, int> a, pair<int, int> b) { return a.second > b.second; });
}