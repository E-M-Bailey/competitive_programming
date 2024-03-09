#include <bits/stdc++.h>

using namespace std;

int constexpr PTS[31]{ 101, 76, 61, 51, 46, 41, 37, 33, 30, 27, 25, 23, 21, 19, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };

int main()
{
	int n, m, r = 0;
	cin >> n >> m;
	n--;
	m--;
	int me = 0;
	for (int j = 0; j < n; j++)
	{
		int a;
		cin >> a;
		me += a;
	}

	if (me == 0)
	{
		cout << m + 1;
		return 0;
	}

	vector<int> S;
	for (int i = 0; i < m;)
	{
		int s = 0;
		for (int j = 0; j < n; j++)
		{
			int a;
			cin >> a;
			s += a;
		}
		if (s > me)
		{
			r++;
			m--;
		}
		else
		{
			S.push_back(s);
			i++;
		}
	}

	m = min(m, 100);
	sort(rbegin(S), rend(S));
	S.resize(m);


}