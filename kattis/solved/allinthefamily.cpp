#include <bits/stdc++.h>

using namespace std;

unordered_map<string, int> N;
vector<string> S;
vector<vector<int>> C;
vector<int> P, D;

int id()
{
	string s;
	cin >> s;
	auto [it, ins] = N.emplace(s, (int)N.size());
	if (ins)
	{
		S.push_back(move(s));
		C.emplace_back();
		P.push_back(-1);
	}
	return it->second;
}

string ord(int n)
{
	string s = to_string(n);
	if (n % 10 == 1 && n % 100 != 11)
		s += "st";
	else if (n % 10 == 2 && n % 100 != 12)
		s += "nd";
	else if (n % 10 == 3 && n % 100 != 13)
		s += "rd";
	else
		s += "th";
	return s;
}

string smul(string const &s, int n)
{
	string t;
	t.reserve(s.size() * n);
	while (n--)
		t += s;
	return t;
}

char const *times(int n)
{
	return n == 1 ? "time" : "times";
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t, p;
	cin >> t >> p;

	while (t--)
	{
		int v = id();
		int d;
		cin >> d;
		while (d--)
		{
			int w = id();
			P[w] = v;
			C[v].push_back(w);
		}
	}

	int n = (int)N.size();

	int root = -1;
	for (int i = 0; i < n; i++)
		if (P[i] < 0)
			root = i;

	D.resize(n);
	vector<int> st;
	st.push_back(root);
	while (!st.empty())
	{
		int v = st.back();
		st.pop_back();
		for (int w : C[v])
		{
			D[w] = D[v] + 1;
			st.push_back(w);
		}
	}

	while (p--)
	{
		int a = id(), b = id();
		string const &A = S[a], &B = S[b];
		int x = 0, y = 0;
		while (D[a] > D[b])
		{
			a = P[a];
			x++;
		}
		while (D[a] < D[b])
		{
			b = P[b];
			y++;
		}
		while (a != b)
		{
			a = P[a];
			b = P[b];
			x++;
			y++;
		}
		if (x == 0)
			cout << B << " is the " << (y == 1 ? "child" : smul("great ", y - 2) + "grandchild") << " of " << A << '\n';
		else if (y == 0)
			cout << A << " is the " << (x == 1 ? "child" : smul("great ", x - 2) + "grandchild") << " of " << B << '\n';
		else if (x == y)
			cout << A << " and " << B << " are " << (x == 1 ? "siblings" : ord(x - 1) + " cousins") << '\n';
		else
			cout << A << " and " << B << " are " << ord(min(x, y) - 1) << " cousins, " << abs(x - y) << ' ' << times(abs(x - y)) << " removed" << '\n';
	}
}
