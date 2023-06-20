#include <bits/stdc++.h>
using namespace std;
struct bezout { __int128_t x, y, g; };
bezout extended_euclid(__int128_t a, __int128_t b) {
	if (b == 0) return {1, 0, a};
	auto [x, y, g] = extended_euclid(b, a % b);
	return {y, x - a / b * y, g};
}
int main() {
	long long T, a1, a2, n1, n2, x, K;
	cin >> T;
	while (T--) {
		cin >> a1 >> n1 >> a2 >> n2;
		K = n1 * n2;
		auto [k1, k2, g] = extended_euclid(n1, n2);
		// 128-bit ints are needed to prevent overflow here.
		cout << (long long)((a2 * k1 * n1 + a1 * k2 * n2) % K + K) % K << ' ' << K << '\n';
	}
}