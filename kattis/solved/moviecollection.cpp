#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
template<typename T>
using os_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
void go()
{
	int m, r;
	cin >> m >> r;
	int t = 0;
	vector<int> P(m);
	iota(P.begin(), P.end(), 0);
	os_set<int> S;
	for (int i = 0; i < m; i++)
		S.insert(i);
	while (r--)
	{
		int a;
		cin >> a;
		a--;
		cout << S.order_of_key(P[a]) << ' ';
		S.erase(P[a]);
		P[a] = --t;
		S.insert(P[a]);
	}
	cout << endl;
}

int main()
{
	int t;
	cin >> t;
	while (t--)
		go();
}