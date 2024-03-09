#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}

	int w, h, f, n;
	cin >> w >> h >> f >> n;

	vector<string> A;
	{
		string a;
		while (cin >> a)
			A.push_back(move(a));
	}

	vector<string> L;
	for (string &a : A)
	{
		if ((int)a.size() > w)
			a.resize(w);
		bool c = !L.empty() && !L.back().empty();
		if (L.empty() || (int)L.back().size() + (int)a.size() + c > w)
			L.emplace_back();
		else if (c)
			L.back() += ' ';
		L.back() += a;
	}
	int l = (int)L.size();

	int t = (h - 3) * f / (l - h) + 1;

	cout << '+' << string(w, '-') << "+-+\n";
	for (int i = 0; i < h; i++)
	{
		L[i + f].resize(w, ' ');
		cout << '|' << L[i + f] << '|';
		if (i == 0)
			cout << '^';
		else if (i == h - 1)
			cout << 'v';
		else if (i == t)
			cout << 'X';
		else
			cout << ' ';
		cout << "|\n";
	}
	cout << '+' << string(w, '-') << "+-+\n";
}