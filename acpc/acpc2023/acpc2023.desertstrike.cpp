#include <bits/stdc++.h>

using namespace std;

int64_t constexpr MOD = 1000000009;

int main()
{
	int64_t K, W;
	cin >> K >> W;
	int64_t n = W / K, T = K * n * (n - 1) + n * (K + (K + 1) / 2), S = W - 2 * W / K;
	//cerr << T << ' ' << S << ' ';
	S *= S;
	if (n * K + (K + 1) / 2 <= W)
		T += n * K + (K + 1) / 2;
	//cerr << T << endl;
	cout << (4 * T + S) % MOD;
}