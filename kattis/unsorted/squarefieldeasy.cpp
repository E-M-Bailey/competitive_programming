#include <bits/stdc++.h>

using namespace std;

template<class T>
constexpr T MAX = numeric_limits<T>::max();
template<class T>
constexpr T MIN = numeric_limits<T>::min();

int n, k;
vector<pair<int, int>> P;

template<class F>
bool k_permutations_helper(vector<vector<int>>& cur, int i, F& f)
{
	if (i == n)
		return f(cur);

	int lim = min((int)size(cur), i + 1);
	for (int j = 0; j < lim; j++)
	{
		cur[j].push_back(i);
		if (k_permutations_helper(cur, i + 1, f))
			return true;
		cur[j].pop_back();
	}
	return false;
}

template<class F>
bool k_permutations(F& f)
{
	vector<vector<int>> cur(k);
	for (auto& set : cur)
		set.reserve(k);
	return k_permutations_helper(cur, 0, f);
}

void go()
{
	cin >> n >> k;
	int Mx = 0, My = 0;
	P.resize(n);
	for (auto& [x, y] : P)
	{
		cin >> x >> y;
		Mx = max(Mx, x);
		My = max(My, y);
	}


	int len;
	const auto f = [&len](const vector<vector<int>>& partition)
	{
		for (const auto& set : partition)
		{
			if (size(set) <= 1) continue;
			int mx = MAX<int>, Mx = MIN<int>, my = MAX<int>, My = MIN<int>;
			for (int i : set)
			{
				auto [x, y] = P[i];
				mx = min(x, mx);
				Mx = max(x, Mx);
				my = min(y, my);
				My = max(y, My);
			}
			if (Mx - mx > len || My - my > len)
				return false;
		}
		//cerr << ' ' << len << endl;
		//for (const auto& set : partition)
		//{
		//	for (int x : set)
		//		cerr << x << ' ';
		//	cerr << endl;
		//}
		//cerr << endl;
		return true;
	};

	int lo = 2, hi = max(Mx, My);
	while (lo < hi)
	{
		len = (lo + hi) / 2;
		if (k_permutations(f))
			hi = len;
		else
			lo = len + 1;
	}
	cout << lo << endl;

}

int main(int argc, const char* argv[])
{
	if (argc >= 3)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++)
	{
		cout << "Case #" << i << ": ";
		//cerr << "Case #" << t + 1 << ": \n";
		go();
	}

}