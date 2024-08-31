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
	n *= 2;
	vector<bool> A(n);
	for (int i = 0; i < n; i++)
	{
		char c;
		cin >> c;
		A[i] = c == '1';
	}
	if (A[0] != A[n - 1] || accumulate(begin(A), end(A), 0) % 2)
	{
		cout << "-1\n";
		return;
	}

	string s;
	for (int i = 0; i * 2 < n; i++)
		s += "()";

	vector<string> ans;
	if (A[0])
		for (int i = 0; i < n; i++)
			A[i] = !A[i];
	else
		ans.push_back(s);

	ans.push_back(s);
	for (int i = 1; i < n - 1; i += 2)
		if (A[i + 1])
		{
			swap(ans.back()[i], ans.back()[i + 1]);
			A[i]	 = !A[i];
			A[i + 1] = !A[i + 1];
		}

	vector<pair<int, int>> B;
	bool				   p = false;
	ans.push_back(s);
	for (int i = 1; i < n - 1; i += 2)
	{
		if (!A[i])
			continue;
		if (p)
		{
			swap(ans.back()[i], ans.back()[i + 1]);
			A[i]			= !A[i];
			A[i + 1]		= !A[i + 1];
			B.back().second = i + 1;
		}
		else
			B.emplace_back(i, 0);
		p = !p;
	}
	
	ans.push_back(s);
	for (auto [i, j] : B)
	{
		swap(ans.back()[i], ans.back()[j]);
		A[i] = !A[i];
		A[j] = !A[j];
	}

	cout << size(ans) << '\n';
	for (string const &t : ans)
		cout << t << '\n';
}
