#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;

	__gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> S;
	while (k--)
	{
		char c;
		cin >> c;
		if (c == 'F')
		{
			int i;
			cin >> i;
			if (!S.insert(i).second)
				S.erase(i);
		}
		else
		{
			int l, r;
			cin >> l >> r;

			auto L = S.lower_bound(l);
			int lct = L == S.end() ? S.size() : S.order_of_key(*L);
			auto R = S.upper_bound(r);
			int rct = R == S.end() ? S.size() : S.order_of_key(*R);
			cout << rct - lct << '\n';
		}
	}
}