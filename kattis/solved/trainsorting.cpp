#include <bits/stdc++.h>
using namespace std;

template<class C>
struct lis
{
	const C c;
	vector<int> E;
	lis(C&& cmp = C{}): c(cmp) {}
	int add(int x)
	{
		auto it = lower_bound(begin(E), end(E), x, c);
		int ans = it - begin(E);
		//cerr << x << ' ' << ans << endl;
		if (it == end(E))
			E.push_back(x);
		else
			*it = x;
		return ans;
	}
};

int main()
{
	int n;
	cin >> n;
	vector<int> A(n);
	for (int& a : A)
		cin >> a;
	lis<less<int>> LIS;
	lis<greater<int>> LDS;
	int best = 0;
	while (!A.empty())
	{
		int a = A.back();
		A.pop_back();
		best = max(best, LIS.add(a) + LDS.add(a) + 1);
	}

	cout << best;
}