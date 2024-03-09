#include <bits/stdc++.h>

using namespace std;

int64_t constexpr MOD = 1000000007;
int64_t constexpr PHI = 1000000006;

int64_t constexpr mpow(int64_t a, int64_t b)
{
	a = a % MOD;
	if (a < 0)
		a += MOD;
	b = b % PHI;
	if (b < 0)
		b += PHI;
	int64_t ans = 1;
	for (; b; b /= 2, a = a * a % MOD)
		if (b % 2)
			ans = ans * a % MOD;
	return ans;
}

int main()
{
	int T;
	cin >> T;
	while (T--)
	{
		int64_t k, n, R;
		cin >> k >> n >> R;

		// 1 / R, 1 / (1 - R)
		int64_t const inv_r = mpow(R, -1), inv_1mr = mpow(1 - R, -1);

		// kth degree Taylor series at R for 1 + x + ... + x^n
		vector<int64_t> B(k + 1);

		// 1 + x + ... + x^n = (x^(n + 1) - 1) / (x - 1) = (-1 + x^(n + 1)) * -1 / (1 - R) * 1 / (1 - (x - R) / (1 - R))
		// ~ (nCr(n + 1, 0) R^(n + 1) + ... + nCr(n + 1, k) R^(n + 1 - k) (x - R)^k - 1) * (-1 / (1 - R) - ... - (x - R)^k / (1 - R)^(k + 1)) (truncated to degree k)
		{
			// (nCr(n + 1, 0) R^(n + 1) + ... + nCr(n + 1, k) R^(n + 1 - k) (x - R)^k) * (1 / (1 - R) + ... + (x - R)^k / (1 - R)^(k + 1))
			// -nCr(n + 1, i) R^(n + 1 - i)
			int64_t coeff_st = MOD - mpow(R, n + 1);
			for (int i = 0; i <= k; i++)
			{
				// -nCr(n + 1, i) R^(n + 1 - i)
				int64_t coeff = coeff_st;
				for (int j = 0; i + j <= k; j++)
				{
					// -nCr(n + 1, i) R^(n + 1 - i) / (1 - R)^(j + 1)
					coeff = coeff * inv_1mr % MOD;
					B[i + j] += coeff;
				}
				coeff_st = coeff_st * (n + 1 - i) % MOD * mpow(R * (i + 1), -1) % MOD;
			}

			// -1 * (-1 / (1 - R) - ... - (x - R)^k / (1 - R)^(k + 1))
			B[0] = inv_1mr;
			for (int i = 1; i <= k; i++)
				B[i] = B[i - 1] * inv_1mr % MOD;
		}

		// take derivative and multiply by x k times
		for (int i = 0; i < k; i++)
		{
			// derivative (B.back() is not updated but it is removed later anyway)
			for (int j = 1; i + j <= k; j++)
				B[j - 1] = B[j] * j;

			// multiply by x = R + (x - R) and truncate to degree k - i - 1
			for (int j = k - i; j > 0; j--)
				B[j] = (B[j + 1] * (j + 1) * R + B[j] * j)
				B.pop_back();
		}
	}

}