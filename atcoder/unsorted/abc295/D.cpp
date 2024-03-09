#include <bits/stdc++.h>
using namespace std;

int main()
{
	string s;
	cin >> s;
	array<int, 1 << 10> C{};
	int o = 0;
	int64_t ans = 0;
	for (char c : s)
	{
		C[o]++;
		o ^= 1 << (c - '0');
		ans += C[o];
	}
	cout << ans << endl;
}