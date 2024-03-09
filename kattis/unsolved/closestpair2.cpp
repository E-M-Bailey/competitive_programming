#include <bits/stdc++.h>

using namespace std;

typedef long double T;

struct entry
{
	T	 x, y;
	bool del;
};

bool operator<(entry l, entry r)
{
	return l.x > r.x;
}

int main()
{
	int n;
	while (cin >> n, n)
	{
		T ans = 200000;

		map<T, T>			  F;
		priority_queue<entry> Q;
		for (int i = 0; i < n; i++)
		{
			T x, y;
			cin >> x >> y;
			Q.push({x, y, false});
		}

		T t	  = -100000;
		auto const cmp = [&t]()

		do
		{
			auto [x, y, del] = Q.top();
			Q.pop();


		}
		while (!Q.empty());
	}
}