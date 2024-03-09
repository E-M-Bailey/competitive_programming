#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

using namespace std;

int k;

int rec(int t, int i)
{
	if (t == 1)
		return 0;
	int j = rec(t - 1, (i + k - 1) % (t - 1));
	// cerr << t << ' ' << i << ' ' << j << ' ' << j + (j >= i) << endl;
	return j + (j >= i);
}

int main()
{
	int t;
	cin >> t >> k;
	cout << rec(t, k - 1);

	// __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> I;
	// for (int i = 0; i < t; i++)
	// 	I.insert(i);
// 
	// for (int i = 0; t > 1; t--)
	// {
	// 	i = (i + k - 1) % t;
	// 	I.erase(I.find_by_order(i));
	// 	for (int ii : I)
	// 		cerr << ii << ' ';
	// 	cerr << endl;
	// }
	// cout << *I.begin();
}