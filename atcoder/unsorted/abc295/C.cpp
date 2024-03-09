#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	unordered_map<int, int> F;
	int ans = n;
	while (n--) {
		int a;
		cin >> a;
		F[a]++;
	}
	for (auto [a, f] : F)
		ans -= f % 2;
	cout << ans / 2;
}