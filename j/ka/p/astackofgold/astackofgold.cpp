#include <bits/stdc++.h>

using namespace std;

using u64 = uint64_t;

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	u64 w, s;
	cin >> w >> s;
	w -= s * (s + 1) * 14630;
	cout << w / 110;
}
