#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> P, S;
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = make_tuple(P[x], P[P[x]]);
		return x;
	}
	int onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x != y)
		{
			if (S[x] < S[y])
				swap(x, y);
			P[y] = x;
			S[x] += S[y];
		}
		return S[x];
	}
};

void go()
{
	int n;
	cin >> n;

	unordered_map<string, int> ID;
	auto const id = [&ID](string &&s)
		{
			auto it = ID.try_emplace(move(s), (int)ID.size()).first;
			return it->second;
		};

	dso D;
	while (n--)
	{
		string A, B;
		cin >> A >> B;
		int a = id(move(A)), b = id(move(B)), c = max(a, b) + 1;
		while ((int)D.S.size() < c)
		{
			D.S.push_back(1);
			D.P.push_back((int)D.P.size());
		}
		cout << D.onion(a, b) << '\n';
	}
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		go();
	}
}
