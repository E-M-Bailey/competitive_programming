#include <bits/stdc++.h>

using namespace std;

struct dso
{
	vector<int> P, R;
	dso(int n) : P(n), R(n)
	{
		iota(begin(P), end(P), 0);
	}
	int find(int x)
	{
		while (x != P[x])
			tie(x, P[x]) = make_pair(P[x], P[P[x]]);
		return x;
	}
	bool onion(int x, int y)
	{
		x = find(x);
		y = find(y);
		if (x == y)
			return false;
		if (R[x] < R[y])
			swap(x, y);
		R[x] += R[x] == R[y];
		P[y] = x;
	}
};

int main()
{

}