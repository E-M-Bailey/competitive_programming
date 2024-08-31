#include <bits/stdc++.h>
using namespace std;

int main() {
	int64_t n, k;
	cin >> n >> k;
	int ans = 1;
	while (n) {
		n = n * (k - 1) / k;
		ans++;
	}
	cout << ans;
}